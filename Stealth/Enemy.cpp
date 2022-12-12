#include "Enemy.h"
#include "ModelManager.h"
#include "Common.h"
#include <math.h>

using namespace Math3d;

//コンストラクタ
Enemy::Enemy() : EnemyBase()
{
	enemyState = EnemyState::Crawl;
}

//デストラクタ
Enemy::~Enemy()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Enemy::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_BODY));

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[ENEMY_BODY]\n");
	}
}

void Enemy::Finalize()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Activate()
{
	position = POSITION;
	dir = DIR;
}

void Enemy::Update(float deltaTime)
{
	GoBuck(deltaTime);

	//エネミーの位置をセット
	MV1SetPosition(modelHandle, position);
}

void Enemy::GoBuck(float deltaTime)
{

	position += dir * SPEED * deltaTime;


	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット dirを向く
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
}

void Enemy::eUpdate()
{
	switch (enemyState)
	{
	case EnemyState::Crawl:
		break;

	case EnemyState::Tracking:
		break;

	}
}

void Enemy::Draw()
{
	eUpdate();

	MV1DrawModel(modelHandle);
}