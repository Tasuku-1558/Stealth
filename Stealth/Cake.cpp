#include "Cake.h"
#include "ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cakePosition"></param>
Cake::Cake(const VECTOR& cakePosition)
	: alive(true)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, RADIUS(50.0f)
{
	position = cakePosition;
}

/// <summary>
/// デストラクタ
/// </summary>
Cake::~Cake()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Cake::Initialize()
{
	//ケーキのモデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE));

	//モデルのサイズ,回転値,位置を設定
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 活性化処理
/// </summary>
void Cake::Activate()
{
	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// 終了処理
/// </summary>
void Cake::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 更新処理
/// </summary>
void Cake::Update(float deltaTime)
{
	//処理なし
}

/// <summary>
/// ケーキを非アクティブ化
/// </summary>
void Cake::CakeAlive()
{
	alive = true;
	position = position;
}

/// <summary>
/// ケーキに衝突した
/// </summary>
void Cake::HitCake()
{
	alive = false;
}

/// <summary>
/// 描画処理
/// </summary>
void Cake::Draw()
{
	MV1DrawModel(modelHandle);
}