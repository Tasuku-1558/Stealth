#include "Bullet.h"
#include "ModelManager.h"
#include "InputManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="inPlayer">�v���C���[�̃|�C���^</param>
Bullet::Bullet(Player* const inPlayer)
	: cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, alive(false)
	, worldMouse()
	, RADIUS(50.0f)
	, SCALE(0.4)
	, ANGLE(0.0)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, POSITION({ 0.0f, 30.0f, 0.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, INITIAL_WORLD_MOUSE({ 0.0f,30.0f,0.0f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, CURSOR_PATH("pointer.png")
{
	Initialize();
	player = inPlayer;
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

	//�P�[�L���f���̃T�C�Y�Ɖ�]�l��ݒ�
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	//�J�[�\���摜�̓ǂݍ���
	cursorImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, CURSOR_PATH).c_str());

	position = POSITION;

	worldMouse = INITIAL_WORLD_MOUSE;

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = POSITION;
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
/// <param name="cake">�P�[�L�̃|�C���^</param>
void Bullet::MouseMove(Cake* cake)
{
	//�}�E�X�̍��W�擾
	GetMousePoint(&mouseX, &mouseY);
	mouseX -= 960;
	mouseY -= 540;

	//�P�[�L�����񂾂�
	if (!cake->GetAlive())
	{
		//�}�E�X��X,Z���W�̃��[���h���W���v�Z
		worldMouse.x = (float)mouseY * (-3000.0f / 1920.0f) * 1.7f + player->GetPosition().z;
		worldMouse.z = (float)mouseX * (1900.0f / 1080.0f) * 1.5f + player->GetPosition().x;
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
	position = VGet(worldMouse.z, worldMouse.y, worldMouse.x);

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

	DrawRotaGraph(mouseX + 960, mouseY + 540, SCALE, ANGLE, cursorImage, TRUE);
}