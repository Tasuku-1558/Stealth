#include "EffectManager.h"
#include "Effect.h"


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
	effect[0] = new Effect(InputPath(EFFECT_FOLDER_PATH, REPOP_EFFECT_PATH), REPOP_SIZE);
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
/// <param name="number">エフェクトの種類</param>
/// <param name="position">エフェクトの位置</param>
void EffectManager::CreateEffect(int number, VECTOR position)
{
	effect[number]->Update(position);
}

/// <summary>
/// パスの入力
/// </summary>
/// <param name="folderPath">エフェクトフォルダーの名前</param>
/// <param name="effectPath">エフェクトの名前</param>
/// <returns>エフェクトのパス</returns>
string EffectManager::InputPath(string folderPath, string effectPath)
{
	return string(folderPath + effectPath);
}