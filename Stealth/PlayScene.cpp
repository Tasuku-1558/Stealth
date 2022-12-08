#include "PlayScene.h"
#include "DxLib.h"

#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "Field.h"

PlayScene::PlayScene()
		: SceneBase()
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, pUpdate(nullptr)
		, field(nullptr)
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

	//エネミークラス
	enemy = new Enemy();
	enemy->Initialize();

	//デバック用
	field = new Field();
	field->Initialize();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);

	SafeDelete(enemy);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);

	//デバック用
	SafeDelete(field);
}

void PlayScene::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &PlayScene::UpdateStart;

	player->Activate();

	enemy->Activate();

	//デバック用
	field->Activate();
}

void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}
}

void PlayScene::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

void PlayScene::UpdateGame(float deltaTime)
{
	//camera->Update(player);

	player->Update(deltaTime);

	enemy->Update(deltaTime,field);
	
	//デバック用
	field->Update();
}

void PlayScene::Draw()
{
	//プレイヤー描画
	player->Draw();

	//エネミー描画
	enemy->Draw();

	//デバック用
	DrawFormatStringToHandle(100, 50, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "HP : %d", player->GetHP());

	field->Draw();
}