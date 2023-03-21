#include "GoalFlag.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="goalPosition"></param>
GoalFlag::GoalFlag(VECTOR goalPosition)
	: rotate()
	, SIZE({ 1.0f, 1.0f, 1.0f })
	, ROTATE_SPEED_Y(3.0f)
	, RADIUS(50.0f)
{
	position = goalPosition;

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GoalFlag::~GoalFlag()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void GoalFlag::Initialize()
{
	//�S�[���̃��f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::GOAL));

	//���f���̃T�C�Y�ƈʒu��ݒ�
	MV1SetScale(modelHandle, SIZE);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// ����������
/// </summary>
void GoalFlag::Activate()
{
	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// �I������
/// </summary>
void GoalFlag::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void GoalFlag::Update(float deltaTime)
{
	//���f������]������
	rotate.y += ROTATE_SPEED_Y * deltaTime;

	//���f���̉�]�l��ݒ�
	MV1SetRotationXYZ(modelHandle, rotate);
}

/// <summary>
/// �`�揈��
/// </summary>
void GoalFlag::Draw()
{
	MV1DrawModel(modelHandle);
}