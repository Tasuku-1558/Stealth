#include "FourthStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
FourthStage::FourthStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, pUpdate(nullptr)
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
FourthStage::~FourthStage()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void FourthStage::Initialize()
{
}

/// <summary>
/// 終了処理
/// </summary>
void FourthStage::Finalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
void FourthStage::Activate()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::Update(float deltaTime)
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
void FourthStage::UpdateStart(float deltaTime)
{
}

/// <summary>
/// ゲーム中
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateGame(float deltaTime)
{
}

/// <summary>
/// ゴール
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateGoal(float deltaTime)
{
}

/// <summary>
/// ゲームオーバー
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateOver(float deltaTime)
{
}

/// <summary>
/// 描画処理
/// </summary>
void FourthStage::Draw()
{
}