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
#include "HitChecker.h"
#include "CakeParticle.h"
#include "CakeRepopEffect.h"
#include "SecondStageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


const float SecondStage::GOAL_POSITION_X = -5700.0f;	//ゴールの位置
const int   SecondStage::PARTICLE_NUMBER = 500;			//パーティクルの数


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
	, hitChecker(nullptr)
	, secondStageMap(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
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

	//ケーキの再出現エフェクトクラス
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

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
	}

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void SecondStage::Activate()
{
	state = State::START;

	frame = 0.0f;

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

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
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

	//++frame;
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
		//エネミーオブジェクトを最後尾に移動してデータを消す
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

	BallBullet* newBallBullet2 = new BallBullet({ -3000.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet2);
}

/// <summary>
/// ケーキのパーティクルを登録
/// </summary>
/// <param name="newCakeParticle"></param>
void SecondStage::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// ケーキのパーティクルを削除
/// </summary>
/// <param name="deleteCakeParticle"></param>
void SecondStage::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
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
void SecondStage::CakeParticlePop()
{
	for (auto ballBulletPtr : ballBullet)
	{
		//マウスカーソルを左クリックし、且つケーキとバレットが非アクティブ且つパーティクルが出ていないならば
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && ballBulletPtr->bullet->GetAlive() && !ballBulletPtr->cake->GetAlive() && !particleFlag)
		{
			//パーティクルの個数分エントリーする
			for (int i = 0; i < PARTICLE_NUMBER; i++)
			{
				CakeParticle* newCakeParticle = new CakeParticle(ballBulletPtr->bullet->GetPosition());
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
void SecondStage::UpdateStart(float deltaTime)
{
	camera->Update(player->GetPosition());

	//ファーストステージでのライトの方向の設定
	light->Update({ 0.0f,-0.5f,0.0f });

	frame += deltaTime;

	//1.3秒経過したらゲーム画面へ移行
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &SecondStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y , player->GetPosition().z);
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateGame(float deltaTime)
{
	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());
	
	for (auto enemyPtr : enemy)
	{
		enemyPtr->Update(deltaTime, player);
		
		player->FoundEnemy(deltaTime, enemyPtr);
		
		for (auto ballBulletPtr : ballBullet)
		{
			enemyPtr->VisualAngleCake(ballBulletPtr->bullet, deltaTime);
			
			//エネミーがケーキを見つけたならば
			if (enemyPtr->CakeFlag())
			{
				break;
			}
		}
	}

	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	}

	//ケーキのパーティクル出現
	CakeParticlePop();

	//パーティクルを出したら
	if (particleFlag)
	{
		particleInterval += deltaTime;

		//５秒経過したら
		//パーティクルを再度出せるようにする
		if (particleInterval > 5.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}

	hitChecker->Check(secondStageMap->GetModelHandle(), player);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	//エネミーに3回見つかったら
	if (player->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}

	//プレイヤーがゴール地点に辿り着いたら
	if (player->GetPosition().x < GOAL_POSITION_X)
	{
		state = State::GOAL;
		pUpdate = &SecondStage::UpdateGoal;
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

	//ゲーム状態がゲームとゴールの時だけ描画する
	if (state == State::GAME || state == State::GOAL)
	{
		//プレイヤー描画
		player->Draw();

		//エネミー描画
		for (auto enemyPtr : enemy)
		{
			enemyPtr->Draw();
		}

		//ボールバレット管理クラス描画
		for (auto ballBulletPtr : ballBullet)
		{
			ballBulletPtr->Draw();

			uiManager->CakeGetDraw(!ballBulletPtr->cake->GetAlive());
		}
	}

	//ケーキの再出現エフェクト描画
	cakeEffect->Draw();

	//UI管理クラス描画
	uiManager->Draw(state, player->GetPlayerCount());

	//ケーキのパーティクルの描画
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}


	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->GetPlayerCount());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());

	for (auto ballBulletPtr : ballBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBulletPtr->cake->GetAlive());
	}


	//画面効果クラス描画
	fadeManager->Draw();
}