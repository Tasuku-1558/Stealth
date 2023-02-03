#include "SecondStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "BallBullet.h"
#include "Wall.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "SecondStageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


const int SecondStage::GOAL_POSITION = -5900;		//ゴールの位置

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
SecondStage::SecondStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy()
	, pUpdate(nullptr)
	, ballBullet()
	, wall()
	, hitChecker(nullptr)
	, secondStageMap(nullptr)
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
SecondStage::~SecondStage()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void SecondStage::Initialize()
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

	//セカンドステージマップクラス
	secondStageMap = new SecondStageMap();
	secondStageMap->Initialize();

	//エフェクトクラス
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//画面効果クラス
	fadeManager = new FadeManager();

	//出現関数
	EnemyPop();

	BallBulletPop();

	WallPop();
}

/// <summary>
/// 終了処理
/// </summary>
void SecondStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(secondStageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
		DeleteEnemy(enemyPtr);
	}

	for (auto ballBulletPtr : ballBullet)
	{
		SafeDelete(ballBulletPtr);
		DeleteBallBullet(ballBulletPtr);
	}

	for (auto wallPtr : wall)
	{
		SafeDelete(wallPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void SecondStage::Activate()
{
	state = State::START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &SecondStage::UpdateStart;

	player->Activate();

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Activate();
	}

	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Activate();
	}

	cakeEffect->Activate();

	uiManager->Activate();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}

	++frame;
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
	Enemy* newEnemy = new Enemy(secondStageMap->GetMap());
	EntryEnemy(newEnemy);

	Enemy* newEnemy2 = new Enemy(secondStageMap->GetMap2());
	EntryEnemy(newEnemy2);
}

/// <summary>
/// ボールバレットを登録
/// </summary>
/// <param name="newBallBullet"></param>
void SecondStage::EntryBallBullet(BallBullet* newBallBullet)
{
	ballBullet.emplace_back(newBallBullet);
}

/// <summary>
/// ボールバレットを削除
/// </summary>
/// <param name="deleteBallBullet"></param>
void SecondStage::DeleteBallBullet(BallBullet* deleteBallBullet)
{
	//ボールバレットオブジェクトから検索して削除
	auto iter = std::find(ballBullet.begin(), ballBullet.end(), deleteBallBullet);

	if (iter != ballBullet.end())
	{
		//ボールバレットオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, ballBullet.end() - 1);
		ballBullet.pop_back();

		return;
	}
}

/// <summary>
/// ボールバレットの出現
/// </summary>
void SecondStage::BallBulletPop()
{
	BallBullet* newBallBullet = new BallBullet({ -600.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet);

	BallBullet* newBallBullet2 = new BallBullet({ -3500.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet2);
}

/// <summary>
/// 壁を登録
/// </summary>
/// <param name="newWall"></param>
void SecondStage::EntryWall(Wall* newWall)
{
	wall.emplace_back(newWall);
}

/// <summary>
/// 壁を削除
/// </summary>
/// <param name="deleteWall"></param>
void SecondStage::DeleteWall(Wall* deleteWall)
{
	//ボールバレットオブジェクトから検索して削除
	auto iter = std::find(wall.begin(), wall.end(), deleteWall);

	if (iter != wall.end())
	{
		//ボールバレットオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, wall.end() - 1);
		wall.pop_back();

		return;
	}
}

/// <summary>
/// 壁の出現
/// </summary>
void SecondStage::WallPop()
{
	Wall* newWall = new Wall({ -1100.0f,30.0f,0.0f });
	EntryWall(newWall);

	Wall* newWall2 = new Wall({ -2000.0f,30.0f,0.0f });
	EntryWall(newWall2);

	Wall* newWall3 = new Wall({ -4000.0f,30.0f,0.0f });
	EntryWall(newWall3);
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &SecondStage::UpdateGame;
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateGame(float deltaTime)
{
	//セカンドステージでのライトの方向の設定
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());
	
	for (auto enemyPtr : enemy)
	{
		enemyPtr->Update(deltaTime, player);
		
		player->FoundEnemy(deltaTime, enemyPtr);

		for (auto wallPtr : wall)
		{
			enemyPtr->VisualAngleWall(wallPtr->GetPosition());
		}
		
		for (auto ballBulletPtr : ballBullet)
		{
			enemyPtr->VisualAngleCake(ballBulletPtr->bullet, deltaTime);
			
			//エネミーがケーキを見つけたならば
			if (enemyPtr->CakeFlag())
			{
				break;
			}
		}

		//エネミーに3回見つかったら
		if (enemyPtr->GetPlayerCount() == 3)
		{
			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}
	}

	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	}

	hitChecker->Check(secondStageMap->GetModelHandle(), player);

	//プレイヤーがゴール地点に辿り着いたら
	if (player->GetPosition().x < GOAL_POSITION)
	{
		state = State::GOAL;
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

/// <summary>
/// 描画処理
/// </summary>
void SecondStage::Draw()
{
	//背景描画
	backGround->Draw();
	
	//マップ描画
	secondStageMap->Draw();

	//プレイヤー描画
	player->Draw();

	//エネミー描画
	for (auto enemyPtr : enemy)
	{
		enemyPtr->Draw();
	}

	//壁描画
	for (auto wallPtr : wall)
	{
		wallPtr->Draw();
	}

	//ボールバレット管理クラス描画
	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Draw();

		uiManager->CakeGetDraw(!ballBulletPtr->cake->GetAlive());
	}

	//エフェクト描画
	cakeEffect->Draw();

	//UI管理クラス描画
	for (auto enemyPtr : enemy)
	{
		uiManager->Draw(state, enemyPtr->GetPlayerCount());
	}


	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());

	for (auto enemyPtr : enemy)
	{
		DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d\n", enemyPtr->GetPlayerCount());
	}
	for (auto ballBulletPtr : ballBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBulletPtr->cake->GetAlive());
	}


	//画面効果クラス描画
	fadeManager->Draw();
}