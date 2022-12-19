#include "PlayScene.h"
#include "DxLib.h"

#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "Boal.h"
#include "HitChecker.h"
#include "Map.h"

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
	player = new Player();
	player->Initialize();

	//ボールクラス
	boal = new Boal();
	boal->Initialize();

	//マップクラス
	map = new Map();
	map->Initialize();

	//エネミークラス
	enemy = new Enemy();
	enemy->Initialize(map);

	//ヒットチェッカークラス
	hitChecker = new HitChecker();
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

//ゲーム開始前
void PlayScene::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

//ゲーム中
void PlayScene::UpdateGame(float deltaTime)
{

	camera->Update(player);

	player->Update(deltaTime, camera);

	enemy->Update(deltaTime);
	
	if (!hitChecker->Hit())
	{
		boal->Update();
	}
	else
	{
		return;
	}

	hitChecker->Check(player, boal);

}

void PlayScene::Draw()
{
	//マップ描画
	map->Draw();

	//プレイヤー描画
	player->Draw();

	//エネミー描画
	enemy->Draw();

	//デバック用
	DrawFormatStringToHandle(100, 50, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Found : %d", player->GetFind());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), font, "Boal : %d", hitChecker->Hit());

	if (!hitChecker->Hit())
	{
		//ボール描画
		boal->Draw();
	}
	else
	{
		return;
	}

}