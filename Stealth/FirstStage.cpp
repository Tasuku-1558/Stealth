#include "FirstStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
#include "CakeBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "Set.h"
#include "SoundManager.h"


const float FirstStage::GOAL_POSITION_X	= -4000.0f;		//ゴールの位置X座標
const int   FirstStage::PARTICLE_NUMBER = 500;			//パーティクルの数

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
	, cakeBullet(nullptr)
	, hitChecker(nullptr)
	, stageMap(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
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
	//マップモデルの種類、サイズ、回転値、位置を入力する
	stageMap = new StageMap(ModelManager::STAGE1, { 80.0f, 50.0f, 80.0f },
							{ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f }, { -2700.0f, -100.0f, -750.0f });

	stageMap->Initialize();

	//エネミークラス
	//エネミーに行動パターンのリストを設定
	enemy = new Enemy(stageMap->GetMap(0), 1000.0f);

	enemy->Initialize();

	//プレイヤークラス
	player = new Player();
	player->Initialize();

	//ケーキバレット管理クラス
	//ケーキの初期位置を設定
	cakeBullet = new CakeBullet({ -1500.0f,30.0f,0.0f });

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

	SafeDelete(stageMap);

	SafeDelete(cakeEffect);

	SafeDelete(enemy);

	SafeDelete(cakeBullet);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
		DeleteCakeParticle(particlePtr);
	}

	//作成したフォントデータの削除
	DeleteFontToHandle(font);

	SoundManager::GetInstance().DeleteBgm();
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

	SoundManager::GetInstance().PlayBgm();

	player->Activate();

	enemy->Activate();

	cakeBullet->Activate();

	cakeEffect->Activate();

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	uiManager->Activate();

	fadeManager->Activate();
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
	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player, hitChecker);

	enemy->VisualAngleCake(cakeBullet->bullet, deltaTime);

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	cakeBullet->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);

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
		pUpdate = &FirstStage::UpdateOver;
	}

	//プレイヤーがゴール地点に辿り着いたら
	if (player->GetPosition().x < GOAL_POSITION_X)
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

	//フレーム数が2.9秒経過したら
	if (frame > 2.9f)
	{
		Set::GetInstance().SetResult(clear);

		SoundManager::GetInstance().StopBgm();

		//ステージ選択画面へ遷移
		parent->SetNextScene(SceneManager::RESULT);
		return;
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

	//フレーム数が2.8秒経過したら
	if (frame > 2.8f)
	{

		SoundManager::GetInstance().StopBgm();

		//ステージ選択画面へ遷移
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void FirstStage::Draw()
{
	//背景描画
	backGround->Draw();

	//マップ描画
	stageMap->Draw();

	//ゲーム状態がゲームとゴールとオーバーの時だけ描画する
	if (state == State::GAME || state == State::GOAL || state == State::OVER)
	{
		//エネミー描画
		enemy->Draw();

		//プレイヤー描画
		player->Draw();

		//ケーキバレット管理クラス描画
		cakeBullet->Draw();
	}

	//ケーキの再出現エフェクト描画
	cakeEffect->Draw();

	//UI管理クラス描画
	uiManager->Draw(state, player->GetPlayerCount(), hitChecker->UI());
	
	//ケーキを所持しているか描画
	uiManager->CakeGetDraw(cakeBullet->CakeGet());
	
	//ケーキのパーティクルの描画
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	//画面効果クラス描画
	fadeManager->Draw();

	//デバック用
	/*DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->GetPlayerCount());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "CakeAlive : %d\n(1:true 0:false)", cakeBullet->cake->GetAlive());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());*/


}