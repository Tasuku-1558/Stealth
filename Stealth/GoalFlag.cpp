#include "GoalFlag.h"
#include "ModelManager.h"


using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
GoalFlag::GoalFlag(VECTOR pos) : ObjectBase()
	, rotate()
	, SIZE({ 1.0f, 1.0f, 1.0f })
	, ROTATE_SPEED({ 0.0f, 3.0f, 0.0f })
{
	position = pos;
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
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::GOAL));
	MV1SetScale(modelHandle, SIZE);
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
	rotate += ROTATE_SPEED * deltaTime;

	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotate);
}

/// <summary>
/// �`�揈��
/// </summary>
void GoalFlag::Draw()
{
	MV1DrawModel(modelHandle);
}