#include "EffectManager.h"
#include "Effect.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
	: EFFECT_FOLDER_PATH("Data/Effect/")
	, REPOP_EFFECT_PATH("repop.efkefc")
	, REPOP_SIZE(30.0f)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		delete effect[i];
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void EffectManager::Initialize()
{
	//各エフェクトの読み込み
	effect[RESPAWN] = new Effect(Input::InputPath(EFFECT_FOLDER_PATH, REPOP_EFFECT_PATH), REPOP_SIZE);
}

/// <summary>
/// 描画処理
/// </summary>
void EffectManager::Draw()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		effect[i]->Draw();
	}
}

/// <summary>
/// エフェクトの生成
/// </summary>
/// <param name="position">エフェクトの位置</param>
/// <param name="effectType">エフェクトの種類</param>
void EffectManager::CreateEffect(VECTOR position, EffectType effectType)
{
	effect[effectType]->Update(position);
}