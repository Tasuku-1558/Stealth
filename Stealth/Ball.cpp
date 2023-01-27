#include "Ball.h"
#include "ModelManager.h"
#include "HitChecker.h"


const VECTOR Ball::SIZE	= { 2.0f, 2.0f, 2.0f };		//モデルの倍率


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos"></param>
Ball::Ball(VECTOR pos) : ObjectBase()
	, alive(true)
{
	position = pos;
	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
Ball::~Ball()
{
	// 終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void Ball::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BALL));
	MV1SetScale(modelHandle, SIZE);
	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BALL]\n");
	}
}

/// <summary>
/// 活性化処理
/// </summary>
void Ball::Activate()
{
	position = position;
}

/// <summary>
/// 終了処理
/// </summary>
void Ball::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// 更新処理
/// </summary>
void Ball::Update()
{
	//処理なし
}

/// <summary>
/// ボールを非アクティブ化
/// </summary>
void Ball::BallAlive()
{
	alive = true;
	position = position;
}

/// <summary>
/// ボールが生きてるか死んでいるかを判定
/// </summary>
/// <param name="hitChecker"></param>
void Ball::IsAlive(HitChecker* hitChecker)
{
	//ボールに当たったならば
	if (hitChecker->BallHit())
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
void Ball::Draw()
{
	MV1DrawModel(modelHandle);
}