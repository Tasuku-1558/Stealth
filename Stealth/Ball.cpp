#include "Ball.h"
#include "ModelManager.h"
#include "HitChecker.h"


const VECTOR Ball::SIZE		= { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const VECTOR Ball::POSITION = { -1500.0f,30.0f,0.0f };	//モデルの位置

Ball::Ball() : ObjectBase()
	, alive(true)
{
	//処理なし
}

Ball::~Ball()
{
	// 終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Ball::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BALL));
	MV1SetScale(modelHandle, SIZE);

	position = POSITION;

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [BALL]\n");
	}
}

void Ball::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Ball::Activate()
{
}

void Ball::Update(HitChecker* hitChecker)
{
	MV1SetPosition(modelHandle, position);

	IsAlive(hitChecker);
}

/// <summary>
/// ボールを非アクティブ化
/// </summary>
void Ball::SetDead()
{
	alive = true;
	position = POSITION;
}

/// <summary>
/// 生きてるか死んでいるか
/// </summary>
/// <param name="hitChecker"></param>
void Ball::IsAlive(HitChecker* hitChecker)
{

	if (hitChecker->Hit())
	{
		alive = false;

	}
	else
	{
		alive = true;
	}
}

void Ball::Draw()
{
	MV1DrawModel(modelHandle);
}