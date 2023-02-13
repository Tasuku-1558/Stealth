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
#include "CakeBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "StageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


const float ThirdStage::GOAL_POSITION_X = -2800.0f;		//ゴールの位置X座標
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
	, stageMap(nullptr)
	, player(nullptr)
	, enemy()
	, monitoringEnemy()
	, pUpdate(nullptr)
	, cakeBullet()
	, hitChecker(nullptr)
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

	//マップクラス
	//マップモデルの種類、サイズ、回転値、位置を入力する
	stageMap = new StageMap(ModelManager::STAGE3, { 50.0f, 50.0f, 55.0f }, 
							{ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f }, { -2600.0f, -100.0f, 2650.0f });
	stageMap->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

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
	CakeBulletPop();

	EnemyPop();

	MonitoringEnemyPop();
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

	SafeDelete(stageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
	}

	for (auto cakeBulletPtr : cakeBullet)
	{
		SafeDelete(cakeBulletPtr);
	}

	for (auto monitoringEnemyPtr : monitoringEnemy)
	{
		SafeDelete(monitoringEnemyPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
	}

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void ThirdStage::Activate()
{
	state = State::START;

	frame = 0.0f;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &ThirdStage::UpdateStart;

	player->Activate();

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Activate();
	}

	for (auto cakeBulletPtr : cakeBullet)
	{
		cakeBulletPtr->Activate();
	}

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	for (auto monitoringEnemyPtr : monitoringEnemy)
	{
		monitoringEnemyPtr->Activate();
	}

	cakeEffect->Activate();

	uiManager->Activate();

	fadeManager->Activate();
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
	Enemy* newEnemy = new Enemy(stageMap->GetMap(3));
	EntryEnemy(newEnemy);

	Enemy* newEnemy2 = new Enemy(stageMap->GetMap(4));
	EntryEnemy(newEnemy2);
}

/// <summary>
/// 監視エネミーの登録
/// </summary>
/// <param name="newMonitoringEnemy"></param>
void ThirdStage::EntryMonitoringEnemy(MonitoringEnemy* newMonitoringEnemy)
{
	monitoringEnemy.emplace_back(newMonitoringEnemy);
}

/// <summary>
/// 監視エネミーの削除
/// </summary>
/// <param name="deleteMonitoringEnemy"></param>
void ThirdStage::DeleteMonitoringEnemy(MonitoringEnemy* deleteMonitoringEnemy)
{
	//監視エネミーオブジェクトから検索して削除
	auto iter = std::find(monitoringEnemy.begin(), monitoringEnemy.end(), deleteMonitoringEnemy);

	if (iter != monitoringEnemy.end())
	{
		//監視エネミーオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, monitoringEnemy.end() - 1);
		monitoringEnemy.pop_back();

		return;
	}
}

/// <summary>
/// 監視エネミーの出現
/// </summary>
void ThirdStage::MonitoringEnemyPop()
{
	MonitoringEnemy* newMonitoringEnemy = new MonitoringEnemy({ -2850.0f, 0.0f, 3000.0f }, { 1.0f,0.0f,0.0f });
	EntryMonitoringEnemy(newMonitoringEnemy);

	MonitoringEnemy* newMonitoringEnemy2 = new MonitoringEnemy({ -1000.0f, 0.0f, 3000.0f }, { -1.0f,0.0f,0.0f });
	EntryMonitoringEnemy(newMonitoringEnemy2);
}

/// <summary>
/// ケーキバレットを登録
/// </summary>
/// <param name="newCakeBullet"></param>
void ThirdStage::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// ケーキバレットを削除
/// </summary>
/// <param name="deleteCakeBullet"></param>
void ThirdStage::DeleteCakeBullet(CakeBullet* deleteCakeBullet)
{
	//ケーキバレットオブジェクトから検索して削除
	auto iter = std::find(cakeBullet.begin(), cakeBullet.end(), deleteCakeBullet);

	if (iter != cakeBullet.end())
	{
		//ケーキバレットオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, cakeBullet.end() - 1);
		cakeBullet.pop_back();

		return;
	}
}

/// <summary>
/// ケーキバレットの出現
/// </summary>
void ThirdStage::CakeBulletPop()
{
	CakeBullet* newCakeBullet = new CakeBullet({ -1500.0f,30.0f,0.0f });
	EntryCakeBullet(newCakeBullet);

	CakeBullet* newCakeBullet2 = new CakeBullet({ -2000.0f,30.0f,1800.0f });
	EntryCakeBullet(newCakeBullet2);
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
	for (auto cakeBulletPtr : cakeBullet)
	{
		//マウスカーソルを左クリックし、且つケーキとバレットが非アクティブ且つパーティクルが出ていないならば
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && cakeBulletPtr->bullet->GetAlive() && !cakeBulletPtr->cake->GetAlive() && !particleFlag)
		{
			//パーティクルの個数分エントリーする
			for (int i = 0; i < PARTICLE_NUMBER; i++)
			{
				CakeParticle* newCakeParticle = new CakeParticle(cakeBulletPtr->bullet->GetPosition());
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

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Update(deltaTime, player);

		//巡回しているエネミーに見つかったら
		player->FoundEnemy(deltaTime, enemyPtr->Spotted());

		for (auto cakeBulletPtr : cakeBullet)
		{
			enemyPtr->VisualAngleCake(cakeBulletPtr->bullet, deltaTime);

			//monitoringEnemy->VisualAngleCake(cakeBulletPtr->bullet, deltaTime);

			//エネミーがケーキを見つけたならば
			if (enemyPtr->CakeFlag())
			{
				break;
			}
		}
	}

	for (auto monitoringEnemyPtr : monitoringEnemy)
	{
		//監視しているエネミーに見つかったら
		monitoringEnemyPtr->Update(deltaTime, player);

		player->FoundEnemy(deltaTime, monitoringEnemyPtr->Spotted());
	}

	for (auto cakeBulletPtr : cakeBullet)
	{
		cakeBulletPtr->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	}

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

	hitChecker->Check(stageMap->GetModelHandle(), player);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	//エネミーに3回見つかったら
	if (player->GetPlayerCount() == 3)
	{
		state = State::OVER;
		pUpdate = &ThirdStage::UpdateOver;
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
	frame += deltaTime;

	fadeManager->FadeMove();

	//フレーム数が2.9秒経過したら
	if (frame > 2.9f)
	{
		//ステージ選択画面へ遷移
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}
}

/// <summary>
/// ゲームオーバー
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateOver(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//フレーム数が2.8秒経過したら
	if (frame > 2.8f)
	{
		//ステージ選択画面へ遷移
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ThirdStage::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	stageMap->Draw();

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

		//監視エネミーの描画
		for (auto monitoringEnemyPtr : monitoringEnemy)
		{
			monitoringEnemyPtr->Draw();
		}

		//ケーキバレット管理クラス描画
		for (auto cakeBulletPtr : cakeBullet)
		{
			cakeBulletPtr->Draw();

			uiManager->CakeGetDraw(!cakeBulletPtr->cake->GetAlive());
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

	//画面効果クラス描画
	fadeManager->Draw();

	//デバック用
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->GetPlayerCount());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());

	for (auto cakeBulletPtr : cakeBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", cakeBulletPtr->cake->GetAlive());
	}
}