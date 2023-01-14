#include "SecondStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Wall.h"
#include "HitChecker.h"
#include "SecondStageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


SecondStage::SecondStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, player(nullptr)
	, enemy()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, pUpdate(nullptr)
	, ball()
	, wall(nullptr)
	, wall2(nullptr)
	, wall3(nullptr)
	, hitChecker(nullptr)
	, secondStageMap(nullptr)
	, secondStageMap2(nullptr)
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, enemyPop(false)
	, enemyPop2(false)
	, ballPop(false)
	, ballPop2(false)
{
	//処理なし
}

SecondStage::~SecondStage()
{
	//処理なし
}

void SecondStage::Initialize()
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

	//壁クラス
	wall = new Wall(ObjectBase::WALL, { -1100.0f,30.0f,0.0f });
	wall->Initialize();

	//壁2クラス
	wall2 = new Wall(ObjectBase::WALL, { -2000.0f,30.0f,0.0f });
	wall2->Initialize();

	//壁3クラス
	wall3 = new Wall(ObjectBase::WALL, { -4000.0f,30.0f,0.0f });
	wall3->Initialize();

	//セカンドステージマップクラス
	secondStageMap = new SecondStageMap();
	secondStageMap->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();
}

void SecondStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(secondStageMap);

	for (auto ptr : enemy)
	{
		SafeDelete(ptr);
	}

	for (auto ptrb : ball)
	{
		SafeDelete(ptrb);
	}

	SafeDelete(wall);

	SafeDelete(wall2);

	SafeDelete(wall3);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

void SecondStage::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &SecondStage::UpdateStart;

	player->Activate();

	for (auto ptr : enemy)
	{
		ptr->Activate();
	}
}

void SecondStage::Update(float deltaTime)
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
void SecondStage::EntryEnemy(Enemy* newEnemy)
{
	enemy.emplace_back(newEnemy);
}

/// <summary>
/// エネミーを削除
/// </summary>
/// <param name="deleteEnemy"></param>
void SecondStage::DeleteEnemy(Enemy* deleteEnemy)
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
void SecondStage::EnemyPop()
{
	if (!enemyPop)
	{
		Enemy* newEnemy = new Enemy(secondStageMap->GetMap(0));
		EntryEnemy(newEnemy);

		enemyPop = true;
	}

	if (!enemyPop2)
	{
		Enemy* newEnemy = new Enemy(secondStageMap->GetMap2(0));
		EntryEnemy(newEnemy);

		enemyPop2 = true;
	}
}

/// <summary>
/// ボールを登録
/// </summary>
/// <param name="newBall"></param>
void SecondStage::EntryBall(Ball* newBall)
{
	ball.emplace_back(newBall);
}

/// <summary>
/// ボールを削除
/// </summary>
/// <param name="newBall"></param>
void SecondStage::DeleteBall(Ball* deleteBall)
{
	//ボールオブジェクトから検索して削除
	auto iter = std::find(ball.begin(), ball.end(), deleteBall);

	if (iter != ball.end())
	{
		//隕石オブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, ball.end() - 1);
		ball.pop_back();

		return;
	}
}

/// <summary>
/// ボールの出現
/// </summary>
void SecondStage::BallPop()
{
	if (!ballPop)
	{
		Ball* newBall = new Ball({ -600.0f,30.0f,0.0f });
		EntryBall(newBall);
		
		ballPop = true;
	}

	if (!ballPop2)
	{
		Ball* newBall2 = new Ball({ -3500.0f,30.0f,0.0f });
		EntryBall(newBall2);

		ballPop2 = true;
	}
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &SecondStage::UpdateGame;
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateGame(float deltaTime)
{
	camera->Update(player);

	EnemyPop();

	BallPop();
	
	for (auto ptr : enemy)
	{
		ptr->Update(deltaTime, player);

		for (auto ptrb : ball)
		{
			player->Update(deltaTime, camera, ptrb, ptr);

		}
		
		//エネミーに3回見つかったら
		if (ptr->GetPlayerCount() == 3)
		{
			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}
	}

	for (auto ptrb : ball)
	{
		hitChecker->Check(player, ptrb/*, map*/);

		if (ptrb->GetAlive())
		{
			ptrb->Update(hitChecker);
		}
	}

	//fadeManager->FadeMove();

	//プレイヤーがゴール地点に辿り着いたら
	if (player->GetPosition().x < -5900)
	{
		state = GOAL;
		pUpdate = &SecondStage::UpdateGoal;

		
	}
}

/// <summary>
/// ゴール
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

void SecondStage::Draw()
{
	//背景描画
	backGround->Draw();
	
	//マップ描画
	secondStageMap->Draw();

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

	for (auto ptrb : ball)
	{
		if (ptrb->GetAlive())
		{
			//ボール描画
			ptrb->Draw();
		}
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

	for (auto ptrb : ball)
	{
		DrawFormatStringToHandle(100, 270, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", ptrb->GetAlive());
	}

	for (auto ptr : enemy)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "PlayerCount : %d", ptr->GetPlayerCount());
	}
	

	//画面効果クラス描画
	fadeManager->Draw();
}