#include "Player.h"
#include "PreCompiledHeader.h"
#include "Bullet.h"
#include "ModelManager.h"
#include "Camera.h"

using namespace Math3d;

const VECTOR Player::RIGHT_ARM_POSITION = { 150.0f, 0.0f, 110.0f };

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() : PlayerBase()
	, rightArmHandle(0)
	, rightArmPosition()
	, boalGet(false)
	, bullet(nullptr)
{
	playerState = PlayerState::Nomal;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	//終了処理が呼ばれていなければ
	if (modelHandle != NULL || rightArmHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
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

	//ショットクラス
	bullet = new Bullet();
	bullet->Initialize();
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(rightArmHandle);
	rightArmHandle = NULL;

	bullet->Finalize();
}

/// <summary>
/// 活性化処理
/// </summary>
void Player::Activate()
{
	position = POSITION;
	rightArmPosition = RIGHT_ARM_POSITION;

	dir = DIR;

	bullet->Activate();
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update(float deltaTime, Camera* camera)
{
	Move(deltaTime, camera);

	Shoot();
	
	//プレイヤーの位置をセット
	MV1SetPosition(modelHandle, position);

	MV1SetPosition(rightArmHandle, rightArmPosition);

}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move(float deltaTime, Camera* camera)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;
	
	//上下
	if (CheckHitKey(KEY_INPUT_UP))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;
	}
	//左右
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputDirection += camera->GetLeft();
		inputFlag = true;
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
		position += inputDirection * SPEED * deltaTime;

		rightArmPosition += inputDirection * SPEED * deltaTime;

	}

	//z軸が逆を向いているのでdirを180度回転させる
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//モデルに回転をセット dirを向く
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	MV1SetRotationZYAxis(rightArmHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	
}

/// <summary>
/// 弾の発射処理
/// </summary>
void Player::Shoot()
{
	
	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		bullet->Update();
	}
}

void Player::pUpdate()
{
	switch (playerState)
	{
	case PlayerState::Nomal:
		break;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{	
	MV1DrawModel(modelHandle);

	bullet->Draw();

	//MV1DrawModel(rightArmHandle);
}