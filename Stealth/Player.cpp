#include "Player.h"
#include "Common.h"
#include "ModelManager.h"

using namespace Math3d;

const VECTOR Player::RIGHT_ARM_POSITION = { -150.0f, 200.0f, -5.0f };

//コンストラクタ
Player::Player() : PlayerBase()
	, rightArmHandle(0)
	, rightArmPosition()
{
	//処理なし
}

//デストラクタ
Player::~Player()
{
	//終了処理が呼ばれていなければ
	if (modelHandle != NULL || rightArmHandle != NULL)
	{
		Finalize();
	}
}

//初期化処理
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_BODY));
	

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[PLAYER_BODY]\n");
	}

	rightArmHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER_ARM));

	//読み込み失敗でエラー
	if (rightArmHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗[PLAYER_ARM]\n");
	}
}

//終了処理
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(rightArmHandle);
	rightArmHandle = NULL;
}

//活性化処理
void Player::Activate()
{
	position = POSITION;
	rightArmPosition = RIGHT_ARM_POSITION;
}

//更新処理
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	//プレイヤーの位置をセット
	MV1SetPosition(modelHandle, position);


	MV1SetPosition(rightArmHandle, rightArmPosition);
}

//移動処理
void Player::Move(float deltaTime)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	//上下
	if (CheckHitKey(KEY_INPUT_UP))
	{
		inputDirection.z -= 1.0f;
		inputFlag = true;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputDirection.z += 1.0f;
		inputFlag = true;
	}
	//左右
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputDirection.x -= 1.0f;
		inputFlag = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputDirection.x += 1.0f;
		inputFlag = true;
	}

	//十字キーの入力があったら
	if (inputFlag)
	{
		//十字キーの入力方向を正規化
		inputDirection = VNorm(inputDirection);

		//十字キーの移動方向に移動
		position += inputDirection * SPEED * deltaTime;

		rightArmPosition += inputDirection * SPEED * deltaTime;
	}
}

//描画処理
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	MV1DrawModel(rightArmHandle);
}