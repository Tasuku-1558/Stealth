#include "Bullet.h"
#include "ModelManager.h"


using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Bullet::Bullet() : ObjectBase()
	, cursorImage(0)
	, mouseX(0)
	, mouseZ(0)
	, worldMouseX(0.0f)
	, worldMouseY(30.0f)
	, worldMouseZ(0.0f)
	, alive(false)
	, IMAGE_FOLDER_PATH("data/image/")
	, CURSOR_PATH("pointer.png")
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, POSITION({ 0.0f, 30.0f, 0.0f })
	, SCALE(0.4f)
{
	//�����Ȃ�
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
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE);
	MV1SetScale(modelHandle, SIZE);

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

	BulletDead();
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
}

/// <summary>
/// �}�E�X�J�[�\���̈ړ�
/// </summary>
/// <param name="cake"></param>
/// <param name="playerPos"></param>
void Bullet::MouseMove(Cake* cake, VECTOR playerPos)
{
	GetMousePoint(&mouseX, &mouseZ);       //�}�E�X�̍��W�擾
	mouseX -= 960;
	mouseZ -= 540;

	//�P�[�L�����񂾂�
	if (!cake->GetAlive())
	{
		//�}�E�X��X,Z���W�̃��[���h���W���v�Z
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
void Bullet::OnShot()
{
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

	DrawRotaGraph(mouseX + 960, mouseZ + 540, SCALE, 0.0f, cursorImage, TRUE);
}