#include "Cake.h"
#include "ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cakePosition">ケーキの座標</param>
Cake::Cake(const VECTOR& cakePosition)
	: alive(true)
	, RADIUS(50.0f)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
{
	position = cakePosition;

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Cake::~Cake()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Cake::Initialize()
{
	//ケーキモデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE));

	//ケーキモデルのサイズと回転値と位置を設定
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);
	MV1SetPosition(modelHandle, position);

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
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
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