#include "FirstStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "BallBullet.h"
#include "Wall.h"
#include "HitChecker.h"
#include "FirstStageMap.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "UiManager.h"
#include "FadeManager.h"


const int FirstStage::GOAL_POSITION	  = -4000;	//ゴールの位置
const int FirstStage::PARTICLE_NUMBER = 500;	//パーティクルの数

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
FirstStage::FirstStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy(nullptr)
	, pUpdate(nullptr)
	, ballBullet(nullptr)
	, wall(nullptr)
	, hitChecker(nullptr)
	, firstStageMap(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, frame(0.0f)
	, pushFlag(false)
	, particleInterval(0.0f)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
FirstStage::~FirstStage()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void FirstStage::Initialize()
{
	//カメラクラス
	camera = new Camera();
	camera->Initialize();

	//ライトクラス
	light = new Light();
	
	//背景クラス
	backGround = new BackGround();
	backGround->Initialize();

	//マップクラス
	firstStageMap = new FirstStageMap();
	firstStageMap->Initialize();

	//エネミークラス
	//エネミーに行動パターンのリストを設定
	enemy = new Enemy(firstStageMap->GetMap());
	enemy->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//ボールバレット管理クラス
	//ケーキの初期位置を設定
	ballBullet = new BallBullet({ -1500.0f,30.0f,0.0f });

	//壁クラス
	//壁の初期位置を設定
	wall = new Wall({ -2500.0f,30.0f,0.0f });
	wall->Initialize();
	
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
}

/// <summary>
/// 終了処理
/// </summary>
void FirstStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(firstStageMap);

	SafeDelete(cakeEffect);

	SafeDelete(enemy);

	SafeDelete(ballBullet);

	SafeDelete(wall);

	SafeDelete(hitChecker);

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
void FirstStage::Activate()
{
	state = State::START;
	frame = 0.0f;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &FirstStage::UpdateStart;

	player->Activate();

	enemy->Activate();

	ballBullet->Activate();

	cakeEffect->Activate();

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	uiManager->Activate();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新
	}

	//++frame;
}

/// <summary>
/// ケーキのパーティクルを登録
/// </summary>
/// <param name="newCakeParticle"></param>
void FirstStage::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// ケーキのパーティクルを削除
/// </summary>
/// <param name="deleteCakeParticle"></param>
void FirstStage::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
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
void FirstStage::CakeParticlePop()
{
	//マウスカーソルを左クリックし、且つケーキとバレットが非アクティブ且つパーティクルが出ていないならば
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && ballBullet->bullet->GetAlive() && !ballBullet->cake->GetAlive() && !pushFlag)
	{
		//パーティクルの個数分エントリーする
		for (int i = 0; i < PARTICLE_NUMBER; i++)
		{
			CakeParticle* newCakeParticle = new CakeParticle(ballBullet->bullet->GetPosition());
			EntryCakeParticle(newCakeParticle);
		}

		pushFlag = true;
	}
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateStart(float deltaTime)
{
	camera->Update(player->GetPosition());

	//ファーストステージでのライトの方向の設定
	light->Update({ 0.0f,-0.5f,0.0f });

	frame += deltaTime;

	//1.3秒経過したらゲーム画面へ移行
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &FirstStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y - 100.0f, player->GetPosition().z);
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGame(float deltaTime)
{
	//ファーストステージでのライトの方向の設定
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player);

	enemy->VisualAngleCake(ballBullet->bullet, deltaTime);

	enemy->VisualAngleWall(wall->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy);

	ballBullet->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);

	//ケーキのパーティクル出現
	CakeParticlePop();

	//パーティクルを出したら
	if (pushFlag)
	{
		particleInterval += deltaTime;

		//５秒経過したら
		//パーティクルを再度出せるようにする
		if (particleInterval > 5.0f)
		{
			pushFlag = false;
			particleInterval = 0.0f;
		}
	}
	
	hitChecker->Check(firstStageMap->GetModelHandle(), player);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}
	
	//プレイヤーがゴール地点に辿り着いたら
	if (player->GetPosition().x < GOAL_POSITION)
	{
		state = State::GOAL;
		pUpdate = &FirstStage::UpdateGoal;
	}

	//エネミーに3回見つかったら
	if (player->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::SELECTION);
		return;
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
void FirstStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	//ステージ選択画面へ遷移
	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

/// <summary>
/// 描画処理
/// </summary>
void FirstStage::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	firstStageMap->Draw();

	//ゲーム状態がゲームとゴールの時だけ描画する
	if (state == State::GAME || state == State::GOAL)
	{
		//エネミー描画
		enemy->Draw();

		//プレイヤー描画
		player->Draw();

		//ボールバレット管理クラス描画
		ballBullet->Draw();
	}

	//壁描画
	//wall->Draw();

	//ケーキの再出現エフェクト描画
	cakeEffect->Draw();

	//UI管理クラス描画
	uiManager->Draw(state, player->GetPlayerCount(), hitChecker->UI());

	//ケーキを所持しているか描画
	uiManager->CakeGetDraw(!ballBullet->cake->GetAlive());
	
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
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "CakeAlive : %d\n(1:true 0:false)", ballBullet->cake->GetAlive());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());


	//画面効果クラス描画
	fadeManager->Draw();

}