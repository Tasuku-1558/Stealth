#include "PlayScene.h"
#include "DxLib.h"

#include "Common.h"
#include "Player.h"
#include "Camera.h"

PlayScene::PlayScene()
		: SceneBase()
		, state()
		, player(nullptr)
		, camera(nullptr)
		, pUpdate(nullptr)
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

	//プレイヤークラス
	player = new Player();
	player->Initialize();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(player);
}

void PlayScene::Activate()
{
	state = START;
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

void PlayScene::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

void PlayScene::UpdateGame(float deltaTime)
{
	camera->Update();

	player->Update(deltaTime);
	
}

void PlayScene::Draw()
{
	//プレイヤー描画
	player->Draw();

	camera->Draw();
}