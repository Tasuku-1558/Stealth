#include "Ball.h"
#include "ModelManager.h"


const VECTOR Ball::SIZE		= { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const VECTOR Ball::POSITION = { -1500.0f,30.0f,0.0f };	//モデルの位置

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos"></param>
Ball::Ball(const VECTOR& pos) : ObjectBase()
	, alive(true)
{
	position = pos;
	Initialize();
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

void Ball::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BALL));
	MV1SetScale(modelHandle, SIZE);

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

void Ball::Update(bool hit)
{
	MV1SetPosition(modelHandle, position);

	IsAlive(hit);
}

/// <summary>
/// ボールを非アクティブ化
/// </summary>
void Ball::SetDead()
{
	alive = true;
	position = position;
}

/// <summary>
/// 生きてるか死んでいるか
/// </summary>
/// <param name="hit"></param>
void Ball::IsAlive(bool hit)
{
	//当たったならば
	if (hit)
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