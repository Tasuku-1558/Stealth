#include "Json.h"
#include "GameScene.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"

#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "CakeParticle.h"
#include "EffectManager.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "Set.h"

#include "StageCreator.h"

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
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
	, GAME_FONT_SIZE(50)
	, FONT_THICK(1)
	, PARTICLE_NUMBER(500)
	, PLAYER_HP(2)
	, GAME_START_COUNT(1.3f)
	, MAX_PARTICLE_INTERVAL(5.0f)
	, PARTICLE_INTERVAL(0.0f)
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

	for (auto CakeBulletPtr : cakeBullet)
	{
		DeleteCakeBullet(CakeBulletPtr);
	}
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

	player = new Player(effectManager, hitChecker);

	stageNo = Set::GetInstance().GetStage();

	if (stageNo == 1)
	{
		for (auto itr = stageCreator.begin(); itr != stageCreator.end(); ++itr) 
		{
			(*itr) = new StageCreator();
		}

		//エネミーに行動パターンのナンバーとスピードを設定
		enemy = new Enemy(GameData::doc["EnemyMovePattern"]["stage1"].GetInt(), GameData::doc["EnemySpeed"]["stage1"].GetFloat());

		//ゴールフラグの初期位置を設定
		goalFlag = new GoalFlag({ GameData::doc["GoalPosition"]["x"].GetFloat(),
								  GameData::doc["GoalPosition"]["y"].GetFloat(),
								  GameData::doc["GoalPosition"]["z"].GetFloat() });
	}
	if (stageNo == 2)
	{
		for (auto itr = stageCreator.begin(); itr != stageCreator.end(); ++itr)
		{
			(*itr) = new StageCreator();
		}

		//エネミーに行動パターンのナンバーとスピードを設定
		enemy = new Enemy(GameData::doc["EnemyMovePattern"]["stage2"].GetInt(), GameData::doc["EnemySpeed"]["stage1"].GetFloat());

		//ゴールフラグの初期位置を設定
		goalFlag = new GoalFlag({ GameData::doc["GoalPosition"]["x"].GetFloat(),
								  GameData::doc["GoalPosition"]["y"].GetFloat(),
								  GameData::doc["GoalPosition"]["z"].GetFloat() });
	}
	
	uiManager = new UiManager();

	fadeManager = new FadeManager();

	//ケーキの初期位置を設定
	CakeBulletPop();

	//エネミーの初期位置を設定
	EnemyPop();

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
/// ケーキバレットを登録
/// </summary>
/// <param name="newCakeBullet">登録するケーキバレットのポインタ</param>
void GameScene::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// ケーキバレットの削除
/// </summary>
/// <param name="deleteCakeBullet">削除するケーキバレットのポインタ</param>
void GameScene::DeleteCakeBullet(CakeBullet* deleteCakeBullet)
{
	//ケーキのパーティクルオブジェクトから検索して削除
	auto iter = std::find(cakeBullet.begin(), cakeBullet.end(), deleteCakeBullet);

	if (iter != cakeBullet.end())
	{
		//ケーキのパーティクルオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, cakeBullet.end() - 1);
		cakeBullet.pop_back();

		return;
	}
}

/// <summary>
/// ケーキバレットの出現
/// </summary>
void GameScene::CakeBulletPop()
{
	//ケーキの座標を設定
	CakeBullet* newCakeBullet = new CakeBullet({ GameData::doc["CakePosition"]["stage1"]["x"].GetFloat(),
												 GameData::doc["CakePosition"]["stage1"]["y"].GetFloat(),
												 GameData::doc["CakePosition"]["stage1"]["z"].GetFloat() }, effectManager, player);
	EntryCakeBullet(newCakeBullet);

	CakeBullet* newCakeBullet2 = new CakeBullet({ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
												  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
												  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() }, effectManager, player);
	EntryCakeBullet(newCakeBullet2);
}

/// <summary>
/// エネミーを登録
/// </summary>
/// <param name="newEnemy">登録するエネミーのポインタ</param>
void GameScene::EntryEnemy(Enemy* newEnemy)
{
}

/// <summary>
/// エネミーの削除
/// </summary>
/// <param name="deleteEnemy">削除するエネミーのポインタ</param>
void GameScene::DeleteEnemy(Enemy* deleteEnemy)
{
}

/// <summary>
/// エネミーの出現
/// </summary>
void GameScene::EnemyPop()
{
}

/// <summary>
/// ケーキのパーティクルを登録
/// </summary>
/// <param name="newCakeParticle">登録するケーキパーティクルのポインタ</param>
void GameScene::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// ケーキのパーティクルを削除
/// </summary>
/// <param name="deleteCakeParticle">削除するケーキパーティクルのポインタ</param>
void GameScene::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
{
	//ケーキのパーティクルオブジェクトから検索して削除
	auto iter = std::find(cakeParticle.begin(), cakeParticle.end(), deleteCakeParticle);

	if (iter != cakeParticle.end())
	{
		//ケーキのパーティクルオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, cakeParticle.end() - 1);
		cakeParticle.pop_back();

		return;
	}
}

/// <summary>
/// ケーキのパーティクルの出現
/// </summary>
void GameScene::CakeParticlePop()
{
	for (auto CakeBulletPtr : cakeBullet)
	{
		//マウスカーソルを左クリックし、且つケーキとバレットが非アクティブ且つパーティクルが出ていないならば
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && CakeBulletPtr->bullet->GetAlive() && !CakeBulletPtr->cake->GetAlive() && !particleFlag)
		{
			//パーティクルの個数分エントリーする
			for (int i = 0; i < PARTICLE_NUMBER; i++)
			{
				CakeParticle* newCakeParticle = new CakeParticle(CakeBulletPtr->bullet->GetPosition());
				EntryCakeParticle(newCakeParticle);
			}

			particleFlag = true;
		}
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

	enemy->Update(deltaTime, player);

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

	player->Update(deltaTime);

	player->FoundEnemy(deltaTime, enemy->Spotted());

	enemy->Update(deltaTime, player);

	for (auto CakeBulletPtr : cakeBullet)
	{
		enemy->VisualAngleCake(CakeBulletPtr->bullet, deltaTime);
		
		//エネミーがケーキを見つけたならば
		if (enemy->CakeFlag())
		{
			break;
		}
	}

	for (auto CakeBulletPtr : cakeBullet)
	{
		CakeBulletPtr->Update(deltaTime);
	}

	goalFlag->Update(deltaTime);

	//ケーキのパーティクル出現
	CakeParticlePop();

	//パーティクルを出したら
	if (particleFlag)
	{
		particleInterval += deltaTime;

		//5秒経過したら
		//パーティクルを再度出せるようにする
		if (particleInterval > MAX_PARTICLE_INTERVAL)
		{
			particleFlag = false;
			particleInterval = PARTICLE_INTERVAL;
		}
	}
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	hitChecker->Check(0, player, &cakeBullet, /*&enemy,*/ goalFlag);
	hitChecker->EnemyAndPlayer(player, enemy);

	ChangeScreen();

	for (auto particlePtr : cakeParticle)
	{
		//パーティクルを出し終わったら
		if (particlePtr->IsParticleEnd())
		{
			DeleteCakeParticle(particlePtr);
		}
	}
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

	for (auto itr = stageCreator.begin(); itr != stageCreator.end(); ++itr)
	{
		(*itr)->Draw();
	}

	enemy->Draw();

	//ゲーム状態がスタートではないならば
	if (gameState != GameState::START)
	{
		player->Draw();
		
		for (auto CakeBulletPtr : cakeBullet)
		{
			CakeBulletPtr->Draw();

			uiManager->CakeGetDraw(CakeBulletPtr->CakeGet());
		}
	}

	goalFlag->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UiHit());
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	fadeManager->Draw();

	//デバック用
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), gameFontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), gameFontHandle, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), gameFontHandle, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), gameFontHandle, "ParticleSize : %d", cakeParticle.size());
#endif // DEBUG
}