#include "Bullet.h"
#include "ModelManager.h"


const VECTOR Bullet::SIZE  = { 2.0f, 2.0f, 2.0f };			//���f���̔{��
const float  Bullet::SPEED = 800.0f;						//���f���̃X�s�[�h
const string Bullet::IMAGE_FOLDER_PATH = "data/image/";     //image�t�H���_�܂ł̃p�X
const string Bullet::CURSOR_PATH	   = "pointer.png";		//�J�[�\���摜�̃p�X


using namespace Math3d;

Bullet::Bullet(Object BALL)
	: cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, worldMouseX(0.0f)
	, worldMouseY(0.0f)
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

	position = VGet(0.0f, 30.0f, 0.0f);

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BALL]\n");
	}

	string failePath = IMAGE_FOLDER_PATH + CURSOR_PATH;
	cursorImage = LoadGraph(failePath.c_str());
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	DeleteGraph(cursorImage);
}

void Bullet::Activate()
{
}

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
void Bullet::MouseMove(Ball* ball, VECTOR pos)
{
	GetMousePoint(&mouseX, &mouseY);                //�}�E�X�̍��W�擾
	mouseX -= 960;
	mouseY -= 540;

	if (!ball->GetAlive())
	{
		worldMouseX = (float)mouseX * (3000.0f / 1920.0f) * 2.0f + pos.z;
		worldMouseY = (float)mouseY * (1900.0f / 1080.0f) * 1.8f + pos.x;
	}
}

/// <summary>
/// �o���b�g���A�N�e�B�u��
/// </summary>
void Bullet::SetDead()
{
	alive = false;
}

/// <summary>
/// �o���b�g���A�N�e�B�u��
/// </summary>
void Bullet::SetAlive()
{
	alive = true;
}

/// <summary>
/// ���������ꂽ��
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::OnShot(float deltaTime)
{
	position = VGet(worldMouseY, 30.0f, worldMouseX);

	MV1SetPosition(modelHandle, position);
}

void Bullet::Draw()
{
	if (alive)
	{
		MV1DrawModel(modelHandle);
	}

	DrawRotaGraph(mouseX + 960, mouseY + 540, 0.04f, 0, cursorImage, TRUE);
}