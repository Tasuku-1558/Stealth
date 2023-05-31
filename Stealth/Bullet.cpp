#include "Bullet.h"
#include "ModelManager.h"
#include "InputManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bullet::Bullet()
	: halfModel(0)
	, cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, alive(false)
	, worldMouse()
	, SCREEN_WIDTH_HALF(960)
	, SCREEN_HEIGHT_HALF(540)
	, RADIUS(50.0f)
	, MOUSE_X_WIDTH(-3000.0f)
	, MOUSE_Z_HEIGHT(1900.0f)
	, MOUSE_X_ADJUSTMENT(1.7f)
	, MOUSE_Z_ADJUSTMENT(1.5f)
	, SCALE(0.4)
	, ANGLE(0.0)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, INITIAL_POSITION({ 0.0f, 30.0f, 0.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, CURSOR_PATH("pointer.png")
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bullet::~Bullet()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Bullet::Initialize()
{
	//�P�[�L���f���̓ǂݍ���
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE);

	//�P�[�L�����̃��f���̓ǂݍ���
	halfModel = ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE_HALF);

	//�P�[�L���f���̃T�C�Y�Ɖ�]�l��ݒ�
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	//�P�[�L�����̃��f���̃T�C�Y�Ɖ�]�l��ݒ�
	MV1SetScale(halfModel, SIZE);
	MV1SetRotationXYZ(halfModel, ROTATE);

	//�J�[�\���摜�̓ǂݍ���
	cursorImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, CURSOR_PATH).c_str());

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = INITIAL_POSITION;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// �I������
/// </summary>
void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);

	MV1DeleteModel(halfModel);

	DeleteGraph(cursorImage);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Bullet::Update(float deltaTime)
{
	OnShot();

	//�����蔻�苅�̈ړ�����
	collisionSphere.Move(position);
}

/// <summary>
/// �}�E�X�J�[�\���̈ړ�
/// </summary>
/// <param name="alive">�P�[�L�������Ă��邩����ł��邩</param>
/// <param name="playerPosition">�v���C���[�̍��W</param>
void Bullet::MouseMove(bool alive, VECTOR playerPosition)
{
	//�}�E�X�̍��W�擾
	GetMousePoint(&mouseX, &mouseY);
	mouseX -= SCREEN_WIDTH_HALF;
	mouseY -= SCREEN_HEIGHT_HALF;

	//�P�[�L�����񂾂�
	if (!alive)
	{
		//�}�E�X��X�AZ���W�̃��[���h���W���v�Z
		worldMouse.x = (float)mouseY * (MOUSE_X_WIDTH / SCREEN_WIDTH) * MOUSE_X_ADJUSTMENT + playerPosition.z;
		worldMouse.z = (float)mouseX * (MOUSE_Z_HEIGHT / SCREEN_HEIGHT) * MOUSE_Z_ADJUSTMENT + playerPosition.x;
	}
}

/// <summary>
/// �o���b�g���A�N�e�B�u��
/// </summary>
void Bullet::BulletDead()
{
	alive = false;
	position = INITIAL_POSITION;
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
	position = { worldMouse.z, worldMouse.y, worldMouse.x };

	//�P�[�L�̈ʒu��ݒ�
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
	
	//MV1DrawModel(halfModel);

	DrawRotaGraph(mouseX + SCREEN_WIDTH_HALF, mouseY + SCREEN_HEIGHT_HALF, SCALE, ANGLE, cursorImage, TRUE);
}