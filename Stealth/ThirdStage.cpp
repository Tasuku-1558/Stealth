#include "ThirdStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "ThirdStageMap.h"
#include "UiManager.h"


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
	, pUpdate(nullptr)
	, ballBullet()
	, hitChecker(nullptr)
	, cakeEffect(nullptr)
	, thirdStageMap(nullptr)
	, uiManager(nullptr)
	, font(0)
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
/// ゲーム開始前
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &ThirdStage::UpdateGame;
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGame(float deltaTime)
{
	//サードステージでのライトの方向の設定
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(), hitChecker->MapHit());

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

	//プレイヤー描画
	player->Draw();
}