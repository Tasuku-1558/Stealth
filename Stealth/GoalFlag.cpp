#include "GoalFlag.h"
#include "ModelManager.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos"></param>
GoalFlag::GoalFlag(VECTOR pos) : ObjectBase()
	, rotate()
	, SIZE({ 1.0f, 1.0f, 1.0f })
	, ROTATE_SPEED({ 0.0f, 3.0f, 0.0f })
	, RADIUS(50.0f)
{
	position = pos;

	Initialize();
	Activate();
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
	//ゴールのモデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::GOAL));

	//モデルのサイズと位置を設定
	MV1SetScale(modelHandle, SIZE);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 活性化処理
/// </summary>
void GoalFlag::Activate()
{
	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
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
	//モデルを回転させる
	rotate += ROTATE_SPEED * deltaTime;

	//モデルの回転値を設定
	MV1SetRotationXYZ(modelHandle, rotate);
}

/// <summary>
/// 描画処理
/// </summary>
void GoalFlag::Draw()
{
	MV1DrawModel(modelHandle);
}