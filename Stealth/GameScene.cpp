#include "Json.h"
#include "GameScene.h"

#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageBlock.h"
#include "Player.h"
#include "Enemy.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "EffectManager.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "StageData.h"
#include "Set.h"


//デバック用
#define DEBUG

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
	: SceneBase(SceneType::GAME)
	, gameState(GameState::START)
	, pUpdate(nullptr)
	, gameFontHandle(0)
	, stageNo(0)
	, gameStartCount(0.0f)
	, clear(true)
	, stagePos()
	, MAX_STAGE_NUMBER(2)
	, FIRST_STAGE_NUMBER(1)
	, SECOND_STAGE_NUMBER(2)
	, GAME_FONT_SIZE(50)
	, FONT_THICK(1)
	, PLAYER_HP(2)
	, MAX_GAME_START_COUNT(1.5f)
	, STAGE_POS_Y(-100.0f)
{
	GameData::doc.ParseStream(GameData::isw);

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	DeleteFontToHandle(gameFontHandle);
}

/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize()
{
	camera = new Camera();

	light = new Light();
	
	backGround = new BackGround();

	effectManager = new EffectManager();

	player = new Player(effectManager);

	hitChecker = new HitChecker();

	stageNo = Set::GetInstance().GetStage();

	StageList stageList[] =
	{
		{FIRST_STAGE_NUMBER,  "Stage1", 2, 1},
		{SECOND_STAGE_NUMBER, "Stage2", 1, 1},
	};

	for (int i = 0; i < MAX_STAGE_NUMBER; i++)
	{
		if (stageNo == stageList[i].number)
		{
			stageData = new StageData();

			StagePop(stageData->s);

			goalFlag = new GoalFlag({ GameData::doc["GoalPosition"][stageList[i].name]["x"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["y"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["z"].GetFloat() });

			CakeBulletPop(stageList[i].number, stageList[i].name, stageList[i].cakeNumber);

			EnemyPop(stageList[i].number, stageList[i].name, stageList[i].enemyNumber);
		}
	}
	
	uiManager = new UiManager();

	fadeManager = new FadeManager();

	//ゲームフォントの読み込み
	gameFontHandle = CreateFontToHandle("Oranienbaum", GAME_FONT_SIZE, FONT_THICK);

	pUpdate = &GameScene::UpdateStart;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
SceneType GameScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}

	return nowSceneType;
}

/// <summary>
/// ステージの出現
/// </summary>
/// <param name="stageData">ステージのデータ</param>
void GameScene::StagePop(int stageData[BLOCK_NUM_Z][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_Z; i++)
	{
		for (int j = 0; j < BLOCK_NUM_X; j++)
		{
			stagePos.x = i * 300.0f;
			stagePos.z = j * -300.0f;

			if (stageData[j][i] == 0)
			{
				activeStage.emplace_back(new StageBlock(stagePos, { 1.0f,1.0f,1.0f }));
			}
		}
	}

	stagePos.y = STAGE_POS_Y;
}

/// <summary>
/// ケーキバレットの出現
/// </summary>
/// <param name="number">ステージの番号</param>
/// <param name="stageName">ステージの名前</param>
/// <param name="cakeNumber">ケーキの数</param>
void GameScene::CakeBulletPop(int number, char stageName[7], int cakeNumber)
{
	if (number == FIRST_STAGE_NUMBER)
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"][stageName]["1"]["x"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["y"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["z"].GetFloat() },

			{ GameData::doc["CakePosition"][stageName]["2"]["x"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["2"]["y"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["2"]["z"].GetFloat() }
		};
	}
	else
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"][stageName]["1"]["x"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["y"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["z"].GetFloat() },
		};
	}

	for (int i = 0; i < cakeNumber; i++)
	{
		activeCakeBullet.emplace_back(new CakeBullet(cakeBulletPosition[i], effectManager, player));
	}
}

/// <summary>
/// エネミーの出現
/// </summary>
/// <param name="number">ステージの番号</param>
/// <param name="stageName">ステージの名前</param>
/// <param name="enemyNumber">敵の数</param>
void GameScene::EnemyPop(int number, char stageName[7], int enemyNumber)
{
	if (number == FIRST_STAGE_NUMBER)
	{
		enemyMovePattern =
		{
			{GameData::doc["EnemyMovePattern"][stageName].GetInt()},
		};

		enemySpeed =
		{
			{GameData::doc["EnemySpeed"][stageName].GetFloat()},
		};
	}
	else
	{
		enemyMovePattern =
		{
			{GameData::doc["EnemyMovePattern"][stageName].GetInt()},
		};

		enemySpeed =
		{
			{GameData::doc["EnemySpeed"][stageName].GetFloat()},
		};
	}

	for (int i = 0; i < enemyNumber; i++)
	{
		//エネミーに行動パターンのナンバーとスピードを設定
		activeEnemy.emplace_back(new Enemy(enemyMovePattern[i], enemySpeed[i]));
	}
}

/// <summary>
/// シーンを入力
/// </summary>
/// <param name="decision">ゲームクリアかゲームオーバーか</param>
void GameScene::InputScene(bool decision)
{
	fadeManager->FadeMove();

	//フェードが終わったら
	if (fadeManager->FadeEnd())
	{
		Set::GetInstance().SetResult(decision);

		//リザルト画面へ遷移
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// 画面を変える
/// </summary>
void GameScene::ChangeScreen()
{
	//エネミーに2回見つかったら
	if (player->FindCount() == PLAYER_HP)
	{
		gameState = GameState::OVER;
		pUpdate = &GameScene::UpdateOver;
	}

	//プレイヤーがゴール地点に辿り着いたら
	if (hitChecker->GoalHit())
	{
		gameState = GameState::GOAL;
		pUpdate = &GameScene::UpdateGoal;
	}
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void GameScene::UpdateStart(float deltaTime)
{
	gameStartCount += deltaTime;

	backGround->Update();

	camera->Update(player->GetPosition());

	for (auto itr = activeEnemy.begin(); itr != activeEnemy.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}

	effectManager->CreateEffect(player->GetPosition(), EffectManager::RESPAWN);

	//1.5秒経過したらゲーム画面へ移行
	if (gameStartCount > MAX_GAME_START_COUNT)
	{
		gameState = GameState::GAME;
		pUpdate = &GameScene::UpdateGame;
	}
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void GameScene::UpdateGame(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	player->Update(deltaTime);

	for (auto itr = activeEnemy.begin(); itr != activeEnemy.end(); ++itr)
	{
		player->FoundEnemy(deltaTime, (*itr)->Spotted());

		(*itr)->Update(deltaTime);
	}

	for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}

	goalFlag->Update(deltaTime);

	hitChecker->Check(deltaTime, &activeStage, player, &activeCakeBullet, &activeEnemy, goalFlag);

	ChangeScreen();
}

/// <summary>
/// ゴール
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void GameScene::UpdateGoal(float deltaTime)
{
	InputScene(clear);
}

/// <summary>
/// ゲームオーバー
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void GameScene::UpdateOver(float deltaTime)
{
	InputScene(!clear);
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	for (auto itr = activeStage.begin(); itr != activeStage.end(); ++itr)
	{
		(*itr)->Draw();
	}

	goalFlag->Draw();

	for (auto itr = activeEnemy.begin(); itr != activeEnemy.end(); ++itr)
	{
		(*itr)->Draw();
	}

	//ゲーム状態がスタートではないならば
	if (gameState != GameState::START)
	{
		player->Draw();
		
		for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
		{
			(*itr)->Draw();

			uiManager->CakeGetDraw((*itr)->CakeGet());
		}
	}

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UiHit());
	
	fadeManager->Draw();

	//デバック用
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), gameFontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), gameFontHandle, "Z : %.0f", player->GetPosition().z);
#endif // DEBUG
}