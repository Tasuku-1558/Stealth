#include "Json.h"
#include "GameScene.h"
#include "DxLib.h"

#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "EffectManager.h"
#include "UiManager.h"
#include "FadeManager.h"
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
	, frame(0.0f)
	, clear(true)
	, MAX_STAGE_NUMBER(2)
	, FIRST_STAGE_NUMBER(1)
	, SECOND_STAGE_NUMBER(2)
	, GAME_FONT_SIZE(50)
	, FONT_THICK(1)
	, PLAYER_HP(2)
	, GAME_START_COUNT(1.3f)
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

	hitChecker = new HitChecker();

	player = new Player(effectManager);

	stageNo = Set::GetInstance().GetStage();

	StageList stageList[] =
	{
		{FIRST_STAGE_NUMBER,  "stage1", 2},
		{SECOND_STAGE_NUMBER, "stage2", 1},
	};

	for (int i = 0; i < MAX_STAGE_NUMBER; i++)
	{
		if (stageNo == stageList[i].number)
		{
			StagePop(StageData::stage1);

			//エネミーに行動パターンのナンバーとスピードを設定
			enemy = new Enemy(GameData::doc["EnemyMovePattern"][stageList[i].name].GetInt(), GameData::doc["EnemySpeed"][stageList[i].name].GetFloat());

			//ゴールフラグの初期位置を設定
			goalFlag = new GoalFlag({ GameData::doc["GoalPosition"][stageList[i].name]["x"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["y"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["z"].GetFloat() });

			CakeBulletPop(stageList[i].cakeNumber, stageList[i].number);

			EnemyPop(stageList[i].number);
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
void GameScene::StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_Z; i++)
	{
		for (int j = 0; j < BLOCK_NUM_X; j++)
		{
			float posX = i * 300.0f;
			float posZ = j * -300.0f;

			if (stageData[j][i] == 0)
			{
				activeStage.emplace_back(new Stage({ posX, STAGE_POS_Y, posZ }));
			}
		}
	}
}

/// <summary>
/// ケーキバレットの出現
/// </summary>
/// <param name="cakeNumber">ケーキの数</param>
/// <param name="number">ステージの番号</param>
void GameScene::CakeBulletPop(int cakeNumber, int number)
{
	if (number == FIRST_STAGE_NUMBER)
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"]["stage1"]["x"].GetFloat(),
			  GameData::doc["CakePosition"]["stage1"]["y"].GetFloat(),
			  GameData::doc["CakePosition"]["stage1"]["z"].GetFloat() },

			{ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() }
		};
	}
	else
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() },
		};
	}

	for (int i = 0; i < cakeNumber; i++)
	{
		if (stageNo == number)
		{
			activeCakeBullet.emplace_back(new CakeBullet(cakeBulletPosition[i], effectManager, player));
		}
	}
}

/// <summary>
/// エネミーの出現
/// </summary>
/// <param name="number">ステージの番号</param>
void GameScene::EnemyPop(int number)
{
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
	if (hitChecker->FlagHit())
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
	backGround->Update();

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player->GetPosition());

	effectManager->CreateEffect(player->GetPosition(), EffectManager::RESPAWN);

	frame += deltaTime;

	//1.3秒経過したらゲーム画面へ移行
	if (frame > GAME_START_COUNT)
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

	player->Update(deltaTime, hitChecker->MapHit(), hitChecker->Back());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	enemy->Update(deltaTime, player->GetPosition());

	for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
	{
		enemy->VisualAngleCake((*itr)->bullet->GetPosition(), deltaTime);

		//エネミーがケーキを見つけたならば
		if (enemy->CakeFlag())
		{
			break;
		}
	}

	for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}

	goalFlag->Update(deltaTime);

	hitChecker->Check(&activeStage, player, &activeCakeBullet, /*&enemy,*/ goalFlag);
	hitChecker->EnemyAndPlayer(player, enemy);

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

	enemy->Draw();

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

	goalFlag->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UiHit());
	
	fadeManager->Draw();

	//デバック用
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), gameFontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), gameFontHandle, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), gameFontHandle, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), gameFontHandle, "MapHit : %d", hitChecker->MapHit());
#endif // DEBUG
}