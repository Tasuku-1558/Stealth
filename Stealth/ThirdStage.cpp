#include "ThirdStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "BallBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "ThirdStageMap.h"
#include "UiManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
ThirdStage::ThirdStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, light(nullptr)
	, camera(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy()
	, pUpdate(nullptr)
	, ballBullet()
	, hitChecker(nullptr)
	, cakeEffect(nullptr)
	, thirdStageMap(nullptr)
	, uiManager(nullptr)
	, font(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ThirdStage::~ThirdStage()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void ThirdStage::Initialize()
{
	//ライトクラス
	light = new Light();

	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//背景クラス
	backGround = new BackGround();
	backGround->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//サードステージマップクラス
	thirdStageMap = new ThirdStageMap();
	thirdStageMap->Initialize();

	//エフェクトクラス
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();
}

/// <summary>
/// 終了処理
/// </summary>
void ThirdStage::Finalize()
{
	SafeDelete(light);

	SafeDelete(camera);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(thirdStageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
	}

	for (auto ballBulletPtr : ballBullet)
	{
		SafeDelete(ballBulletPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	SafeDelete(uiManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void ThirdStage::Activate()
{
	state = State::START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &ThirdStage::UpdateStart;

	player->Activate();

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Activate();
	}

	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Activate();
	}

	cakeEffect->Activate();

	uiManager->Activate();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &ThirdStage::UpdateGame;
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGame(float deltaTime)
{
	//サードステージでのライトの方向の設定
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(), hitChecker->MapHit());

}

/// <summary>
/// ゴール
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

/// <summary>
/// 描画処理
/// </summary>
void ThirdStage::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	thirdStageMap->Draw();

	//プレイヤー描画
	player->Draw();

	//エネミー描画
	for (auto enemyPtr : enemy)
	{
		enemyPtr->Draw();
	}

	//ボールバレット管理クラス描画
	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Draw();
		uiManager->CakeGetDraw(!ballBulletPtr->cake->GetAlive());
	}

	//エフェクト描画
	cakeEffect->Draw();

	//UI管理クラス描画
	for (auto enemyPtr : enemy)
	{
		uiManager->Draw(state, enemyPtr->GetPlayerCount());
	}


	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());

	for (auto enemyPtr : enemy)
	{
		DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d\n", enemyPtr->GetPlayerCount());
	}
	for (auto ballBulletPtr : ballBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBulletPtr->cake->GetAlive());
	}
}