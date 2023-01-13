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
	, enemy()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, pUpdate(nullptr)
	, ball(nullptr)
	, ball2(nullptr)
	, wall(nullptr)
	, wall2(nullptr)
	, wall3(nullptr)
	, hitChecker(nullptr)
	, stage2Map(nullptr)
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, pop(false)
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
	ball = new Ball({ -600.0f,30.0f,0.0f });
	ball->Initialize();

	ball2 = new Ball({ -3500.0f,30.0f,0.0f });
	ball2->Initialize();

	//壁クラス
	wall = new Wall(ObjectBase::WALL, { -1100.0f,30.0f,0.0f });
	wall->Initialize();

	//壁2クラス
	wall2 = new Wall(ObjectBase::WALL, { -2000.0f,30.0f,0.0f });
	wall2->Initialize();

	//壁3クラス
	wall3 = new Wall(ObjectBase::WALL, { -4000.0f,30.0f,0.0f });
	wall3->Initialize();

	//マップクラス
	stage2Map = new Stage2Map();
	stage2Map->Initialize();

	//エネミークラス
	/*enemy = new Enemy(stage2Map);
	enemy->Initialize();*/

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

	SafeDelete(ball);

	SafeDelete(ball2);

	SafeDelete(wall);

	SafeDelete(wall2);

	SafeDelete(wall3);

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

	for (auto ptr : enemy)
	{
		SafeDelete(ptr);
		ptr->Activate();
	}
}

void Stage2::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}
}

/// <summary>
/// エネミーを登録
/// </summary>
/// <param name="newEnemy"></param>
void Stage2::EntryEnemy(Enemy* newEnemy)
{
	enemy.emplace_back(newEnemy);
}

/// <summary>
/// エネミーを削除
/// </summary>
/// <param name="deleteEnemy"></param>
void Stage2::DeleteEnemy(Enemy* deleteEnemy)
{
	//エネミーオブジェクトから検索して削除
	auto iter = std::find(enemy.begin(), enemy.end(), deleteEnemy);

	if (iter != enemy.end())
	{
		//隕石オブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, enemy.end() - 1);
		enemy.pop_back();

		return;
	}
}

/// <summary>
/// エネミーの出現
/// </summary>
void Stage2::EnemyPop()
{
	if (!pop)
	{
		Enemy* newEnemy = new Enemy(stage2Map);
		EntryEnemy(newEnemy);

		Enemy* newEnemy = new Enemy();
		EntryEnemy(newEnemy);

		pop = true;
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

	EnemyPop();

	for (auto ptr : enemy)
	{
		ptr->Update(deltaTime, player);

		player->Update(deltaTime, camera, ball, ptr);

		//エネミーに3回見つかったら
		if (ptr->GetPlayerCount() == 3)
		{
			parent->SetNextScene(SceneManager::TITLE);
			return;
		}
	}

	hitChecker->Check(player, ball/*, map*/);

	if (ball->GetAlive())
	{
		ball->Update(hitChecker);
	}

	if (ball2->GetAlive())
	{
		ball2->Update(hitChecker);
	}

	//fadeManager->FadeMove();

	//プレイヤーがゴール地点に辿り着いたら
	if (player->GetPosition().x < -5900)
	{
		state = GOAL;
		pUpdate = &Stage2::UpdateGoal;
	}
}

/// <summary>
/// ゴール
/// </summary>
/// <param name="deltaTime"></param>
void Stage2::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
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
	for (auto ptr : enemy)
	{
		ptr->Draw();
	}

	//壁描画
	wall->Draw();

	//壁2描画
	wall2->Draw();

	//壁3描画
	wall3->Draw();

	if (ball->GetAlive())
	{
		//ボール描画
		ball->Draw();
	}

	if (ball2->GetAlive())
	{
		ball2->Draw();
	}

	//UI管理クラス描画
	for (auto ptr : enemy)
	{
		uiManager->Draw(state, ptr);
	}

	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 270, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", ball->GetAlive());

	for (auto ptr : enemy)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "PlayerCount : %d", ptr->GetPlayerCount());
	}
	

	//画面効果クラス描画
	fadeManager->Draw();
}