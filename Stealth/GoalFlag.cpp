#include "GoalFlag.h"
#include "ModelManager.h"
#include "InputManager.h"


using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="goalPosition">�S�[���I�u�W�F�N�g�̈ʒu</param>
GoalFlag::GoalFlag(VECTOR goalPosition)
	: goalImage(0)
	, rotate()
	, ROTATE_SPEED(3.0f)
	, RADIUS(50.0f)
	, GOAL_CENTER_POSITION(0.5f)
	, GOAL_SIZE(4000.0f)
	, GOAL_ANGLE(0.0f)
	, SIZE({ 1.0f, 1.0f, 1.0f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, GOAL_PATH("goal.png")
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

	//�S�[�������̉摜�̓ǂݍ���
	goalImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, GOAL_PATH).c_str());

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

	DeleteGraph(goalImage);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
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

	DrawBillboard3D(position, GOAL_CENTER_POSITION, GOAL_CENTER_POSITION, GOAL_SIZE, GOAL_ANGLE, goalImage, TRUE);
}