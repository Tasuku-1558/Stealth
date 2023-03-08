#include "FirstStage.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"

#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "RepopEffect.h"
#include "CakeParticle.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "Set.h"

//デバック用
#define DEBUG


/// <summary>
/// コンストラクタ
/// </summary>
FirstStage::FirstStage()
	: SceneBase(SceneType::PLAY)
	, state()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy(nullptr)
	, pUpdate(nullptr)
	, cakeBullet(nullptr)
	, hitChecker(nullptr)
	, stageMap(nullptr)
	, goalFlag(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
	, stageNo(0)
	, PARTICLE_NUMBER(500)
	, PLAYER_HP(2)
{
	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
FirstStage::~FirstStage()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void FirstStage::Initialize()
{
	camera = new Camera();

	light = new Light();
	
	backGround = new BackGround();

	stageMap = new StageMap();

	if (stageMap->GetStage() == 1)
	{
		//マップモデルの種類、サイズ、回転値、位置を入力する
		stageMap->Initialize(ModelManager::STAGE1, { 80.0f, 50.0f, 80.0f },
			{ 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }, { -780.0f, -100.0f, 2400.0f });

		//エネミーに行動パターンのリストとスピードを設定
		enemy = new Enemy(stageMap->GetMap(1), 1000.0f);

		//ケーキの初期位置を設定
		cakeBullet = new CakeBullet({ 0.0f,30.0f,1500.0f });

		goalFlag = new GoalFlag({ -50.0f ,0.0f,3700.0f });
	}
	if (stageMap->GetStage() == 2)
	{
		//マップモデルの種類、サイズ、回転値、位置を入力する
		stageMap->Initialize(ModelManager::STAGE2, { 80.0f, 60.0f, 80.0f },
						{ 0.0f, 0.0f, 0.0f }, { -7000.0f, -100.0f, -2900.0f });
		//エネミーに行動パターンのリストとスピードを設定
		enemy = new Enemy(stageMap->GetMap(0), 1000.0f);

		//ケーキの初期位置を設定
		cakeBullet = new CakeBullet({ -1500.0f,30.0f,0.0f });

		//ゴールフラグの位置を設定
		goalFlag = new GoalFlag({ -4000.0f ,0.0f,0.0f });
	}

	player = new Player();

	cakeEffect = new RepopEffect();

	hitChecker = new HitChecker();

	uiManager = new UiManager();

	fadeManager = new FadeManager();
}

/// <summary>
/// 終了処理
/// </summary>
void FirstStage::Finalize()
{
	/*SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(stageMap);

	SafeDelete(enemy);

	SafeDelete(cakeBullet);

	SafeDelete(goalFlag);

	SafeDelete(player);

	SafeDelete(cakeEffect);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);*/

	for (auto particlePtr : cakeParticle)
	{
		DeleteCakeParticle(particlePtr);
		//SafeDelete(particlePtr);
	}

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// 活性化処理
/// </summary>
void FirstStage::Activate()
{
	font = CreateFontToHandle("Oranienbaum", 50, 1);

	state = State::START;
	pUpdate = &FirstStage::UpdateStart;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
SceneType FirstStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//状態ごとに更新

		return nowSceneType;
	}
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
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && cakeBullet->bullet->GetAlive() && !cakeBullet->cake->GetAlive() && !particleFlag)
	{
		//パーティクルの個数分エントリーする
		for (int i = 0; i < PARTICLE_NUMBER; i++)
		{
			CakeParticle* newCakeParticle = new CakeParticle(cakeBullet->bullet->GetPosition());
			EntryCakeParticle(newCakeParticle);
		}

		particleFlag = true;
	}
}

/// <summary>
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateStart(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	cakeEffect->Update(player->GetPosition());

	frame += deltaTime;

	//1.3秒経過したらゲーム画面へ移行
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &FirstStage::UpdateGame;
	}
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGame(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player);

	enemy->VisualAngleCake(cakeBullet->bullet, deltaTime);

	player->Update(deltaTime, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	cakeBullet->Update(deltaTime, player, cakeEffect);

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
	
	hitChecker->Check(stageMap->GetModelHandle(), player, goalFlag);

	hitChecker->EnemyAndPlayer(player, enemy);

	hitChecker->CakeAndPlayer(player, cakeBullet->cake);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}
	
	//エネミーに2回見つかったら
	if (player->FindCount() == PLAYER_HP)
	{
		state = State::OVER;
		pUpdate = &FirstStage::UpdateOver;
	}

	//プレイヤーがゴール地点に辿り着いたら
	if (hitChecker->FlagHit())
	{
		state = State::GOAL;
		pUpdate = &FirstStage::UpdateGoal;
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
	frame += deltaTime;

	fadeManager->FadeMove();

	//フレーム数が3.4秒経過したら
	if (frame > 3.4f)
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
void FirstStage::UpdateOver(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//フレーム数が3.4秒経過したら
	if (frame > 3.4f)
	{
		Set::GetInstance().SetResult(!clear);

		//リザルト画面へ遷移
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void FirstStage::Draw()
{
	backGround->Draw();

	stageMap->Draw();

	//ゲーム状態がスタートではないならば描画する
	if (state != State::START)
	{
		enemy->Draw();

		player->Draw();
		
		cakeBullet->Draw();

		goalFlag->Draw();
	}

	cakeEffect->Draw();

	uiManager->Draw(state, player->FindCount(), hitChecker->UI());
	
	uiManager->CakeGetDraw(cakeBullet->CakeGet());
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	fadeManager->Draw();

	//デバック用
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "CakeAlive : %d\n(1:true 0:false)", cakeBullet->cake->GetAlive());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());
#endif // DEBUG
}