#include "Bullet.h"
#include "ModelManager.h"


const VECTOR Bullet::SIZE			   = { 2.0f, 2.0f, 2.0f };	//���f���̔{��
const VECTOR Bullet::POSITION		   = { 0.0f, 30.0f, 0.0f }; //���f���̈ʒu
const string Bullet::IMAGE_FOLDER_PATH = "data/image/";			//image�t�H���_�܂ł̃p�X
const string Bullet::CURSOR_PATH	   = "pointer.png";			//�J�[�\���摜�̃p�X
const float  Bullet::SCALE			   = 0.4f;					//�J�[�\���摜�̑傫��

using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bullet::Bullet()
	: cursorImage(0)
	, mouseX(0)
	, mouseZ(0)
	, worldMouseX(0.0f)
	, worldMouseZ(0.0f)
	, alive(false)
{
	//�����Ȃ�
}

Bullet::~Bullet()
{
	// �I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Bullet::Initialize()
{
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::BALL);
	MV1SetScale(modelHandle, SIZE);

	// �}�E�X�J�[�\����\�����Ȃ�
	SetMouseDispFlag(FALSE);

	position = POSITION;

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BULLET]\n");
	}

	string failePath = IMAGE_FOLDER_PATH + CURSOR_PATH;
	cursorImage = LoadGraph(failePath.c_str());
}

void Bullet::Activate()
{
	position = POSITION;
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	DeleteGraph(cursorImage);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="ball"></param>
void Bullet::Update(float deltaTime, Ball* ball)
{
	if (!ball->GetAlive())
	{
		OnShot(deltaTime);
	}
}

/// <summary>
/// �}�E�X�J�[�\���̈ړ�
/// </summary>
/// <param name="ball"></param>
/// <param name="pos"></param>
void Bullet::MouseMove(Ball* ball, VECTOR playerPos)
{
	GetMousePoint(&mouseX, &mouseZ);                //�}�E�X�̍��W�擾
	mouseX -= 960;
	mouseZ -= 540;

	//�{�[�������񂾂�
	if (!ball->GetAlive())
	{
		//�}�E�X��XZ���W�̃��[���h���W���v�Z
		worldMouseX = (float)mouseX * (3000.0f / 1920.0f) * 1.6f + playerPos.z;
		worldMouseZ = (float)mouseZ * (1900.0f / 1080.0f) * 1.5f + playerPos.x;
	}
}

/// <summary>
/// �o���b�g���A�N�e�B�u��
/// </summary>
void Bullet::BulletDead()
{
	alive = false;
	position = POSITION;
}

/// <summary>
/// �o���b�g���A�N�e�B�u��
/// </summary>
void Bullet::BulletAlive()
{
	alive = true;
}

/// <summary>
/// ���������ꂽ��
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::OnShot(float deltaTime)
{
	position = VGet(worldMouseZ, 30.0f, worldMouseX);

	MV1SetPosition(modelHandle, position);
}

void Bullet::Draw()
{
	if (alive)
	{
		MV1DrawModel(modelHandle);
	}

	DrawRotaGraph(mouseX + 960, mouseZ + 540, SCALE, 0, cursorImage, TRUE);
}