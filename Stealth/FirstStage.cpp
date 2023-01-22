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
#include "Map.h"
#include "Effect.h"
#include "UiManager.h"
#include "FadeManager.h"


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
		, map(nullptr)
		, effect(nullptr)
		, uiManager(nullptr)
		, fadeManager(nullptr)
		, font(0)
{
	//処理なし
}

FirstStage::~FirstStage()
{
	//処理なし
}

void FirstStage::Initialize()
{
	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//ライトクラス
	light = new Light();
	light->Initialize();

	//背景クラス
	backGround = new BackGround();
	backGround->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//ボールバレット管理クラス
	ballBullet = new BallBullet({ -1500.0f,30.0f,0.0f });

	//壁クラス
	wall = new Wall({ -2500.0f,30.0f,0.0f });
	wall->Initialize();

	//マップクラス
	map = new Map();
	map->Initialize();

	//エフェクトクラス
	effect = new Effect();
	effect->Initialize();

	//エネミークラス
	enemy = new Enemy(map->GetMap());
	enemy->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();
}

void FirstStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(map);

	SafeDelete(effect);

	SafeDelete(enemy);

	SafeDelete(ballBullet);

	SafeDelete(wall);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void FirstStage::Activate()
{
	state = State::START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &FirstStage::UpdateStart;

	player->Activate();

	enemy->Activate();

	ballBullet->Activate();

	effect->Activate();

	uiManager->Activate();
}

void FirstStage::Update(float deltaTime)
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
	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player);

	enemy->VisualAngleBall(ballBullet->bullet->GetPosition());

	enemy->VisualAngleWall(wall->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());

	player->EnemyUpdate(enemy);

	ballBullet->Update(deltaTime, hitChecker->Hit(), player->GetPosition(), hitChecker, effect);
	
	hitChecker->Check(map->GetModel(), player);
	
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

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

void FirstStage::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	map->Draw();
	
	//プレイヤー描画
	player->Draw();

	//エネミー描画
	enemy->Draw();

	//壁描画
	wall->Draw();

	//ボールバレット管理クラス描画
	ballBullet->Draw();

	//エフェクト描画
	effect->Draw();

	//UI管理クラス描画
	uiManager->Draw(state, enemy->GetPlayerCount(), hitChecker->UI());

	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBullet->ball->GetAlive());


	//画面効果クラス描画
	fadeManager->Draw();

}