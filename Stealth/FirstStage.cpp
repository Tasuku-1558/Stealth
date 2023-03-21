#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "FirstStage.h"

#include "DxLib.h"
#include "PreCompiledHeader.h"
#include <fstream>

#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
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

namespace Json
{
	const char* filePath = "Data/Json/GameData.json";

	//jsonファイルの解析
	//解析・・・キーの名前をコンテンツとして扱えるようにするための作業（例　doc[キー].GetInt()などで使えるように？
	std::ifstream ifs(filePath);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
}
/// <summary>
/// コンストラクタ
/// </summary>
FirstStage::FirstStage()
	: SceneBase(SceneType::PLAY)
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
	Json::doc.ParseStream(Json::isw);

	Initialize();
	Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
FirstStage::~FirstStage()
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
void FirstStage::Initialize()
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
	enemy = new Enemy(0, Json::doc["Position"]["x"].GetFloat()/*1000.0f*/);

	//ゴールフラグの初期位置を設定
	goalFlag = new GoalFlag({ -50.0f ,0.0f,3700.0f });

	hitChecker = new HitChecker();

	uiManager = new UiManager();

	fadeManager = new FadeManager();

	//ケーキの初期位置を設定
	CakeBulletPop();
}

void FirstStage::stage(int num)
{
	stageNo = num;
}

/// <summary>
/// 活性化処理
/// </summary>
void FirstStage::Activate()
{
	fontHandle = CreateFontToHandle("Oranienbaum", 50, 1);

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
/// ケーキバレットを登録
/// </summary>
/// <param name="newCakeBullet"></param>
void FirstStage::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// ケーキバレットの削除
/// </summary>
/// <param name="deleteCakeBullet"></param>
void FirstStage::DeleteCakeBullet(CakeBullet* deleteCakeBullet)
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
void FirstStage::CakeBulletPop()
{
	//ケーキの座標を設定
	CakeBullet* newCakeBullet = new CakeBullet({ 0.0f,30.0f,1500.0f }, effectManager);
	EntryCakeBullet(newCakeBullet);

	CakeBullet* newCakeBullet2 = new CakeBullet({ 0.0f,30.0f,1000.0f }, effectManager);
	EntryCakeBullet(newCakeBullet2);
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
void FirstStage::UpdateStart(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	effectManager->CreateRepopEffect(player->GetPosition());

	frame += deltaTime;

	//1.3秒経過したらゲーム画面へ移行
	if (frame > 1.3f)
	{
		gameState = GameState::GAME;
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
		pUpdate = &FirstStage::UpdateOver;
	}

	//プレイヤーがゴール地点に辿り着いたら
	if (hitChecker->FlagHit())
	{
		gameState = GameState::GOAL;
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