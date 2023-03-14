#include "Stone.h"
#include "ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stonePosition"></param>
Stone::Stone(const VECTOR& stonePosition)
	: alive(true)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, RADIUS(50.0f)
{
	position = stonePosition;
}

/// <summary>
/// デストラクタ
/// </summary>
Stone::~Stone()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Stone::Initialize()
{
	//小石のモデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STONE));

	//モデルのサイズ,回転値,位置を設定
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 活性化処理
/// </summary>
void Stone::Activate()
{
	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// 終了処理
/// </summary>
void Stone::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 更新処理
/// </summary>
void Stone::Update(float deltaTime)
{
	//当たり判定球の移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// 小石を非アクティブ化
/// </summary>
void Stone::StoneAlive()
{
	alive = true;
	position = position;
}

/// <summary>
/// 描画処理
/// </summary>
void Stone::Draw()
{
	MV1DrawModel(modelHandle);
}