#include "PlayScene.h"
#include "DxLib.h"

#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "Ball.h"
#include "Wall.h"
#include "HitChecker.h"
#include "Map.h"
#include "UiManager.h"
#include "FadeManager.h"


PlayScene::PlayScene()
		: SceneBase()
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, pUpdate(nullptr)
		, ball(nullptr)
		, wall(nullptr)
		, hitChecker(nullptr)
		, map(nullptr)
		, uiManager(nullptr)
		, fadeManager(nullptr)
		, font(0)
{
	//処理なし
}

PlayScene::~PlayScene()
{
	//処理なし
}

void PlayScene::Initialize()
{
	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//ライトクラス
	light = new Light();
	light->Initialize();

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
	map = new Map();
	map->Initialize();

	//エネミークラス
	enemy = new Enemy(map);
	enemy->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);

	SafeDelete(map);

	SafeDelete(enemy);

	SafeDelete(ball);

	SafeDelete(wall);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &PlayScene::UpdateStart;

	player->Activate();
	
}

void PlayScene::Update(float deltaTime)
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
void PlayScene::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateGame(float deltaTime)
{
	camera->Update(player);

	enemy->Update(deltaTime, player);

	player->Update(deltaTime, camera, ball, enemy);
	
	hitChecker->Check(player, ball, map);

	if (ball->GetAlive())
	{
		ball->Update(hitChecker);
	}
	
	//fadeManager->FadeMove();
}

void PlayScene::Draw()
{
	//マップ描画
	map->Draw();

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
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "discovery : %d", enemy->Discovery());
	DrawFormatStringToHandle(100, 450, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());



	//画面効果クラス描画
	fadeManager->Draw();

}