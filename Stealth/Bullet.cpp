#include "Bullet.h"
#include "ModelManager.h"
#include "Player.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bullet::Bullet()
	: cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, worldMouseX(0.0f)
	, worldMouseY(30.0f)
	, worldMouseZ(0.0f)
	, alive(false)
	, IMAGE_FOLDER_PATH("Data/image/")
	, CURSOR_PATH("pointer.png")
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, POSITION({ 0.0f, 30.0f, 0.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, SCALE(0.4f)
	, RADIUS(50.0f)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bullet::~Bullet()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Bullet::Initialize()
{
	//�P�[�L�̃��f���̓ǂݍ���
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE);

	//���f���̃T�C�Y�Ɖ�]�l��ݒ�
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	//�}�E�X�J�[�\����\�����Ȃ�
	SetMouseDispFlag(FALSE);

	string failePath = IMAGE_FOLDER_PATH + CURSOR_PATH;
	cursorImage = LoadGraph(failePath.c_str());
}

/// <summary>
/// ����������
/// </summary>
void Bullet::Activate()
{
	position = POSITION;

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// �I������
/// </summary>
void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);

	DeleteGraph(cursorImage);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::Update(float deltaTime)
{
	OnShot();

	//�����蔻�苅�̈ړ�����
	collisionSphere.Move(position);
}

/// <summary>
/// �}�E�X�J�[�\���̈ړ�
/// </summary>
/// <param name="cake"></param>
/// <param name="player">�v���C���[�̈ʒu</param>
void Bullet::MouseMove(Cake* cake, Player* player)
{
	//�}�E�X�̍��W�擾
	GetMousePoint(&mouseX, &mouseY);
	mouseX -= 960;
	mouseY -= 540;

	//�P�[�L�����񂾂�
	if (!cake->GetAlive())
	{
		//�}�E�X��X,Z���W�̃��[���h���W���v�Z
		worldMouseX = (float)mouseY * (3000.0f / -1920.0f) * 1.7f + player->GetPosition().z;
		worldMouseZ = (float)mouseX * (1900.0f / 1080.0f) * 1.5f + player->GetPosition().x;
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
void Bullet::OnShot()
{
	//���f���̈ʒu��ݒ�
	position = VGet(worldMouseZ, worldMouseY, worldMouseX);

	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// �`�揈��
/// </summary>
void Bullet::Draw()
{
	//�P�[�L�������Ă���Ȃ�
	if (alive)
	{
		MV1DrawModel(modelHandle);
	}

	DrawRotaGraph(mouseX + 960, mouseY + 540, SCALE, 0.0f, cursorImage, TRUE);
}