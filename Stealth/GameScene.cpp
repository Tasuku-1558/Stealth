#include "Json.h"
#include "GameScene.h"

#include "PreCompiledHeader.h"

#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
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

//デバック用
#define DEBUG

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
	: SceneBase(SceneType::GAME)
	, gameState(GameState::START)
	, pUpdate(nullptr)
	, fontHandle(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
	, stageNo(0)
	, PARTICLE_NUMBER(500)
	, PLAYER_HP(2)
{
	GameData::doc.ParseStream(GameData::isw);

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	DeleteFontToHandle(fontHandle);

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

	//マップモデルの種類、サイズ、回転値、位置を入力する
	stageMap = new StageMap(ModelManager::STAGE1, { 80.0f, 50.0f, 80.0f },
		{ 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }, { -780.0f, -100.0f, 2400.0f });

	effectManager = new EffectManager();

	player = new Player(effectManager);

	//エネミーに行動パターンのナンバーとスピードを設定
	enemy = new Enemy(0, GameData::doc["EnemySpeed"]["stage1"].GetFloat());

	//ゴールフラグの初期位置を設定
	goalFlag = new GoalFlag({ GameData::doc["GoalPosition"]["x"].GetFloat(),
							  GameData::doc["GoalPosition"]["y"].GetFloat(),
							  GameData::doc["GoalPosition"]["z"].GetFloat() });

	hitChecker = new HitChecker();

	uiManager = new UiManager();

	fadeManager = new FadeManager();

	//ケーキの初期位置を設定
	CakeBulletPop();

	fontHandle = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &GameScene::UpdateStart;
}

void GameScene::stage(int num)
{
	stageNo = num;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
SceneType GameScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新

		return nowSceneType;
	}
}

/// <summary>
/// ケーキバレットを登録
/// </summary>
/// <param name="newCakeBullet"></param>
void GameScene::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// ケーキバレットの削除
/// </summary>
/// <param name="deleteCakeBullet"></param>
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
												 GameData::doc["CakePosition"]["stage1"]["z"].GetFloat() }, effectManager);
	EntryCakeBullet(newCakeBullet);

	CakeBullet* newCakeBullet2 = new CakeBullet({ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
												  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
												  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() }, effectManager);
	EntryCakeBullet(newCakeBullet2);
}

/// <summary>
/// ケーキのパーティクルを登録
/// </summary>
/// <param name="newCakeParticle"></param>
void GameScene::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// ケーキのパーティクルを削除
/// </summary>
/// <param name="deleteCakeParticle"></param>
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
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateStart(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	effectManager->CreateEffect(0, player->GetPosition());

	frame += deltaTime;

	//1.3秒経過したらゲーム画面へ移行
	if (frame > 1.3f)
	{
		gameState = GameState::GAME;
		pUpdate = &GameScene::UpdateGame;
	}
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateGame(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	player->Update(deltaTime, hitChecker->Back(), hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	enemy->Update(deltaTime, player);

	for (auto CakeBulletPtr : cakeBullet)
	{
		enemy->VisualAngleCake(CakeBulletPtr->bullet, deltaTime);

		if (enemy->CakeFlag())
		{
			break;
		}
	}

	for (auto CakeBulletPtr : cakeBullet)
	{
		CakeBulletPtr->Update(deltaTime, player);
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
		if (particleInterval > 5.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	hitChecker->Check(stageMap->GetModelHandle(), player, &cakeBullet, /*&enemy,*/ goalFlag);
	hitChecker->EnemyAndPlayer(player, enemy);
	
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
/// <param name="deltaTime"></param>
void GameScene::UpdateGoal(float deltaTime)
{
	fadeManager->FadeMove();

	//フェードが終わったら
	if (fadeManager->FadeEnd())
	{
		Set::GetInstance().SetResult(clear);

		//リザルト画面へ遷移
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// ゲームオーバー
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateOver(float deltaTime)
{
	fadeManager->FadeMove();

	//フェードが終わったら
	if (fadeManager->FadeEnd())
	{
		Set::GetInstance().SetResult(!clear);

		//リザルト画面へ遷移
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	stageMap->Draw();

	//ゲーム状態がスタートではないならば描画する
	if (gameState != GameState::START)
	{
		enemy->Draw();

		player->Draw();
		
		for (auto CakeBulletPtr : cakeBullet)
		{
			CakeBulletPtr->Draw();

			uiManager->CakeGetDraw(CakeBulletPtr->CakeGet());
		}
	}

	goalFlag->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UI());
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	fadeManager->Draw();

	//デバック用
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), fontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), fontHandle, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), fontHandle, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), fontHandle, "ParticleSize : %d", cakeParticle.size());
	DrawFormatStringToHandle(100, 600, GetColor(255, 0, 0), fontHandle, "stage : %d", stageNo);
#endif // DEBUG
}