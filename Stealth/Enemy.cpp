#include "Enemy.h"
#include "ModelManager.h"
#include "Common.h"

using namespace Math3d;

//コンストラクタ
Enemy::Enemy() : EnemyBase()
{
	enemyState = EnemyState::Nomal;
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

	if (position.z < -300)
	{
		dir = VGet(-1.0f, 0.0f, 0.0f);

		if (position.x < -450)
		{
			dir = VGet(0.0f, 0.0f, 1.0f);

			if (position.z < 400)
			{
				dir = VGet(.0f, 0.0f, 1.0f);

				
			}
		}
	}

}

void Enemy::eUpdate()
{
	switch (enemyState)
	{
	case EnemyState::Nomal:
		break;

	case EnemyState::Attack:
		break;

	}
}

void Enemy::Draw()
{
	eUpdate();

	MV1DrawModel(modelHandle);
}