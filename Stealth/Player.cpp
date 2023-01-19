#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "Enemy.h"

using namespace Math3d;


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() : PlayerBase()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	//終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[PLAYER]\n");
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// 活性化処理
/// </summary>
void Player::Activate()
{
	position = POSITION;
	dir = DIR;
	speed = SPEED;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="mapHit"></param>
void Player::Update(float deltaTime, Camera* camera, bool mapHit)
{
	Move(deltaTime, camera, mapHit);

	//プレイヤーの位置をセット
	MV1SetPosition(modelHandle, position);

	aio(mapHit);
	
}

void Player::EnemyUpdate(Enemy* enemy)
{
	FoundEnemy(enemy);
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
void Player::Move(float deltaTime, Camera* camera, bool mapHit)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	//上下
	if (CheckHitKey(KEY_INPUT_W))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;

		if(mapHit && dir.x)
		{
			
			speed = 0.0f;
		}
		else
		{
			speed = SPEED;
		}
		
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;

		if(mapHit && dir.x)
		{
			speed = 0.0f;
		}
		else
		{
			speed = SPEED;
		}
	}
	//左右
	if (CheckHitKey(KEY_INPUT_D))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;

		if (mapHit && dir.z)
		{
			speed = 0.0f;
		}
		else
		{
			speed = SPEED;
		}
		
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		inputDirection += camera->GetLeft();
		inputFlag = true;

		if (mapHit && dir.z)
		{
			speed = 0.0f;
		}
		else
		{
			speed = SPEED;
		}
	}

	//十字キーの入力があったら
	if (inputFlag)
	{

		// 左右・上下同時押しなどで入力ベクトルが0の時
		if (VSquareSize(inputDirection) < 0.5f)
		{
			return;
		}

		//十字キーの入力方向を正規化
		inputDirection = VNorm(inputDirection);

		//十字キーの入力方向をキャラの向きとする
		dir = inputDirection;
		
		//十字キーの移動方向に移動
		position += dir * speed * deltaTime;
	}

	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット dirを向く
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// エネミーに見つかった場合
/// </summary>
/// <param name="enemy"></param>
void Player::FoundEnemy(Enemy* enemy)
{
	if (enemy->Discovery())
	{
		WaitTimer(1000);

		//位置と向きを初期化
		position = POSITION;
		dir = DIR;
	}
}

void Player::aio(bool mapHit)
{
	
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{	
	MV1DrawModel(modelHandle);
}