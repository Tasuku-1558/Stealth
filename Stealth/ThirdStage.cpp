#include "ThirdStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "MonitoringEnemy.h"
#include "BallBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "ThirdStageMap.h"
#include "UiManager.h"


const float ThirdStage::GOAL_POSITION_X = -1900.0f;		//ゴールの位置X座標
const float ThirdStage::GOAL_POSITION_Z = 4600.0f;		//ゴールの位置Z座標
const int   ThirdStage::PARTICLE_NUMBER = 500;			//パーティクルの数

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
ThirdStage::ThirdStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, light(nullptr)
	, camera(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy()
	, monitoringEnemy(nullptr)
	, pUpdate(nullptr)
	, ballBullet()
	, hitChecker(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, thirdStageMap(nullptr)
	, uiManager(nullptr)
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
ThirdStage::~ThirdStage()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void ThirdStage::Initialize()
{
	//ライトクラス
	light = new Light();

	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//背景クラス
	backGround = new BackGround();
	backGround->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//サードステージマップクラス
	thirdStageMap = new ThirdStageMap();
	thirdStageMap->Initialize();

	monitoringEnemy = new MonitoringEnemy(thirdStageMap->GetMap2());
	monitoringEnemy->Initialize();

	//ケーキの再出現エフェクトクラス
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//ヒットチェッカークラス
	hitChecker = new HitChecker();

	//UI管理クラス
	uiManager = new UiManager();
	uiManager->Initialize();

	//出現関数
	BallBulletPop();

	EnemyPop();
}

/// <summary>
/// 終了処理
/// </summary>
void ThirdStage::Finalize()
{
	SafeDelete(light);

	SafeDelete(camera);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(thirdStageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
	}

	for (auto ballBulletPtr : ballBullet)
	{
		SafeDelete(ballBulletPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
	}

	SafeDelete(uiManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void ThirdStage::Activate()
{
	state = State::START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &ThirdStage::UpdateStart;

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
void ThirdStage::Update(float deltaTime)
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
void ThirdStage::EntryEnemy(Enemy* newEnemy)
{
	enemy.emplace_back(newEnemy);
}

/// <summary>
/// エネミーを削除
/// </summary>
/// <param name="deleteEnemy"></param>
void ThirdStage::DeleteEnemy(Enemy* deleteEnemy)
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
void ThirdStage::EnemyPop()
{
	Enemy* newEnemy = new Enemy(thirdStageMap->GetMap());
	EntryEnemy(newEnemy);

	Enemy* newEnemy2 = new Enemy(thirdStageMap->GetMap2());
	EntryEnemy(newEnemy2);
}

/// <summary>
/// ボールバレットを登録
/// </summary>
/// <param name="newBallBullet"></param>
void ThirdStage::EntryBallBullet(BallBullet* newBallBullet)
{
	ballBullet.emplace_back(newBallBullet);
}

/// <summary>
/// ボールバレットを削除
/// </summary>
/// <param name="deleteBallBullet"></param>
void ThirdStage::DeleteBallBullet(BallBullet* deleteBallBullet)
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
void ThirdStage::BallBulletPop()
{
	BallBullet* newBallBullet = new BallBullet({ -600.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet);

	BallBullet* newBallBullet2 = new BallBullet({ -1400.0f,30.0f,2000.0f });
	EntryBallBullet(newBallBullet2);

	BallBullet* newBallBullet3 = new BallBullet({ -4000.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet3);
}

/// <summary>
/// ケーキのパーティクルを登録
/// </summary>
/// <param name="newCakeParticle"></param>
void ThirdStage::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// ケーキのパーティクルを削除
/// </summary>
/// <param name="deleteCakeParticle"></param>
void ThirdStage::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
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
void ThirdStage::CakeParticlePop()
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
void ThirdStage::UpdateStart(float deltaTime)
{
	camera->Update(player->GetPosition());

	//サードステージでのライトの方向の設定
	light->Update({ 0.0f,-0.5f,0.0f });

	frame += deltaTime;

	//1.3秒経過したらゲーム画面へ移行
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &ThirdStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGame(float deltaTime)
{
	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(), hitChecker->MapHit());

	monitoringEnemy->Update(deltaTime, player);

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

	hitChecker->Check(thirdStageMap->GetModelHandle(), player);

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
	if (player->GetPosition().x < GOAL_POSITION_X &&
		player->GetPosition().z > GOAL_POSITION_Z)
	{
		state = State::GOAL;
		pUpdate = &ThirdStage::UpdateGoal;
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
void ThirdStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

/// <summary>
/// 描画処理
/// </summary>
void ThirdStage::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	thirdStageMap->Draw();

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

	//monitoringEnemy->Draw();

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
}