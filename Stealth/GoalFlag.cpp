#include "GoalFlag.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="goalPosition">�S�[���I�u�W�F�N�g�̈ʒu</param>
GoalFlag::GoalFlag(VECTOR goalPosition)
	: rotate()
	, ROTATE_SPEED(3.0f)
	, RADIUS(50.0f)
	, SIZE({ 1.0f, 1.0f, 1.0f })
{
	position = goalPosition;

	Initialize();
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
	//�S�[���I�u�W�F�N�g���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::GOAL));

	//���f���̃T�C�Y�ƈʒu��ݒ�
	MV1SetScale(modelHandle, SIZE);
	MV1SetPosition(modelHandle, position);

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
	rotate.y += ROTATE_SPEED * deltaTime;

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