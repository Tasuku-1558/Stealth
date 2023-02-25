#include "GoalFlag.h"
#include "ModelManager.h"


using namespace Math3d;

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
GoalFlag::~GoalFlag()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void GoalFlag::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::GOAL));
	MV1SetScale(modelHandle, SIZE);
}

/// <summary>
/// 終了処理
/// </summary>
void GoalFlag::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void GoalFlag::Update(float deltaTime)
{
	rotate += ROTATE_SPEED * deltaTime;

	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, rotate);
}

/// <summary>
/// 描画処理
/// </summary>
void GoalFlag::Draw()
{
	MV1DrawModel(modelHandle);
}