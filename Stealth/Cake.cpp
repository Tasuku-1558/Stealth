#include "Cake.h"
#include "ModelManager.h"
#include "HitChecker.h"


//const VECTOR Cake::SIZE	= { 20.0f, 20.0f, 20.0f };		//モデルの倍率


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos"></param>
Cake::Cake(const VECTOR& pos) : ObjectBase()
	, alive(true)
	, SIZE({ 20.0f, 20.0f, 20.0f })
{
	position = pos;
	Initialize();
	Activate();
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
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE));
	MV1SetScale(modelHandle, SIZE);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 活性化処理
/// </summary>
void Cake::Activate()
{
	CakeAlive();
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
void Cake::Update()
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
/// ケーキが生きてるか死んでいるかを判定
/// </summary>
/// <param name="hitChecker"></param>
void Cake::IsAlive(HitChecker* hitChecker)
{
	//ケーキに当たったならば
	if (hitChecker->CakeHit())
	{
		alive = false;
	}
	else
	{
		alive = true;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Cake::Draw()
{
	MV1DrawModel(modelHandle);
}