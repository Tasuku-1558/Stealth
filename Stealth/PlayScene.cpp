#include "PlayScene.h"
#include "DxLib.h"

#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "Boal.h"
#include "HitChecker.h"
#include "Map.h"
#include "UiManager.h"


PlayScene::PlayScene()
		: SceneBase()
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, pUpdate(nullptr)
		, boal(nullptr)
		, hitChecker(nullptr)
		, map(nullptr)
		, uiManager(nullptr)
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
	boal = new Boal();
	boal->Initialize();

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
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);

	SafeDelete(map);

	SafeDelete(enemy);

	SafeDelete(boal);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &PlayScene::UpdateStart;

	player->Activate();

	boal->Activate();
	
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

	player->Update(deltaTime, camera, boal, enemy);
	
	hitChecker->Check(player, boal);

	if (boal->GetAlive())
	{
		boal->Update(hitChecker);
	}
	else
	{
		return;
	}
	
}

void PlayScene::Draw()
{
	//マップ描画
	map->Draw();

	//プレイヤー描画
	player->Draw();

	//エネミー描画
	enemy->Draw();

	//UI管理クラス描画
	uiManager->Draw(state);

	//デバック用
	DrawFormatStringToHandle(100, 50, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Found : %d", player->GetFind());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", boal->GetAlive());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "discovery : %d", enemy->Discovery());
	DrawFormatStringToHandle(100, 450, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());

	

	if (boal->GetAlive())
	{
		//ボール描画
		boal->Draw();
	}
	else
	{
		return;
	}


}