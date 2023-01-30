#include "FirstStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "BallBullet.h"
#include "Wall.h"
#include "HitChecker.h"
#include "FirstStageMap.h"
#include "CakeRepopEffect.h"
#include "UiManager.h"
#include "FadeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
FirstStage::FirstStage(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, backGround(nullptr)
		, pUpdate(nullptr)
		, ballBullet(nullptr)
		, wall(nullptr)
		, hitChecker(nullptr)
		, firstStageMap(nullptr)
		, cakeEffect(nullptr)
		, uiManager(nullptr)
		, fadeManager(nullptr)
		, font(0)
		, frame(0)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
FirstStage::~FirstStage()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void FirstStage::Initialize()
{
	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//ライトクラス
	light = new Light();
	
	//背景クラス
	backGround = new BackGround();
	backGround->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//ボールバレット管理クラス
	//ボールの初期位置を設定
	ballBullet = new BallBullet({ -1500.0f,30.0f,0.0f });

	//壁クラス
	//壁の初期位置を設定
	wall = new Wall({ -2500.0f,30.0f,0.0f });
	wall->Initialize();

	//マップクラス
	firstStageMap = new FirstStageMap();
	firstStageMap->Initialize();

	//エフェクトクラス
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//エネミークラス
	//エネミーに行動パターンのリストを設定
	enemy = new Enemy(firstStageMap->GetMap());
	enemy->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();
}

/// <summary>
/// 終了処理
/// </summary>
void FirstStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(firstStageMap);

	SafeDelete(cakeEffect);

	SafeDelete(enemy);

	SafeDelete(ballBullet);

	SafeDelete(wall);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void FirstStage::Activate()
{
	state = State::START;
	frame = 0;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &FirstStage::UpdateStart;

	player->Activate();

	enemy->Activate();

	ballBullet->Activate();

	cakeEffect->Activate();

	uiManager->Activate();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}

	++frame;
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &FirstStage::UpdateGame;

}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGame(float deltaTime)
{
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player);

	enemy->VisualAngleBall(ballBullet->bullet, deltaTime);

	enemy->VisualAngleWall(wall->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(enemy);

	ballBullet->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	
	hitChecker->Check(firstStageMap->GetModel(), player);
	
	//プレイヤーがゴール地点に辿り着いたら
	if (player->GetPosition().x < -4000)
	{
		state = State::GOAL;
		pUpdate = &FirstStage::UpdateGoal;
	}

	//エネミーに3回見つかったら
	if (enemy->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}
}

/// <summary>
/// ゴール
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	//ステージ選択画面へ遷移
	parent->SetNextScene(SceneManager::SELECTION);
	return;

}

/// <summary>
/// 描画処理
/// </summary>
void FirstStage::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	firstStageMap->Draw();
	
	//プレイヤー描画
	player->Draw();

	//エネミー描画
	enemy->Draw();

	//壁描画
	wall->Draw();

	//ボールバレット管理クラス描画
	ballBullet->Draw();

	//エフェクト描画
	cakeEffect->Draw();

	//UI管理クラス描画
	uiManager->Draw(state, enemy->GetPlayerCount(), hitChecker->UI());

	uiManager->CakeGetDraw(!ballBullet->ball->GetAlive());
	

	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBullet->ball->GetAlive());


	//画面効果クラス描画
	fadeManager->Draw();

}