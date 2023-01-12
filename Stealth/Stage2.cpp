#include "Stage2.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Ball.h"
#include "Wall.h"
#include "HitChecker.h"
#include "Stage2Map.h"
#include "UiManager.h"
#include "FadeManager.h"


Stage2::Stage2(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, player(nullptr)
	, enemy(nullptr)
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, pUpdate(nullptr)
	, ball(nullptr)
	, wall(nullptr)
	, hitChecker(nullptr)
	, stage2Map(nullptr)
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
{
	//処理なし
}

Stage2::~Stage2()
{
	//処理なし
}

void Stage2::Initialize()
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
	player = new Player(ObjectBase::PLAYER);
	player->Initialize();

	//ボールクラス
	ball = new Ball();
	ball->Initialize();

	//壁クラス
	wall = new Wall(ObjectBase::WALL);
	wall->Initialize();

	//マップクラス
	stage2Map = new Stage2Map();
	stage2Map->Initialize();

	//エネミークラス
	enemy = new Enemy(stage2Map);
	enemy->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();
}

void Stage2::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(stage2Map);

	SafeDelete(enemy);

	SafeDelete(ball);

	SafeDelete(wall);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void Stage2::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &Stage2::UpdateStart;

	player->Activate();
}

void Stage2::Update(float deltaTime)
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
void Stage2::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &Stage2::UpdateGame;
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void Stage2::UpdateGame(float deltaTime)
{
	camera->Update(player);

	enemy->Update(deltaTime, player);

	player->Update(deltaTime, camera, ball, enemy);

	//hitChecker->Check(player, ball, map, enemy);

	if (ball->GetAlive())
	{
		ball->Update(hitChecker);
	}

	//fadeManager->FadeMove();

	//エネミーに３回見つかったら
	if (enemy->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
}

void Stage2::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	stage2Map->Draw();

	//プレイヤー描画
	player->Draw();

	//エネミー描画
	enemy->Draw();

	//壁描画
	wall->Draw();

	if (ball->GetAlive())
	{
		//ボール描画
		ball->Draw();
	}

	//UI管理クラス描画
	uiManager->Draw(state);

	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 270, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", ball->GetAlive());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());


	//画面効果クラス描画
	fadeManager->Draw();
}