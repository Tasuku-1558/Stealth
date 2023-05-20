#include "Stage.h"
#include "ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">壁モデルの位置</param>
/// <param name="scale">壁モデルの大きさ</param>
Stage::Stage(VECTOR position, VECTOR scale)
{
	//壁モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE));

	//大きさと位置を設定
	MV1SetScale(modelHandle, scale);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Stage::Update(float deltaTime)
{
	//処理なし
}

/// <summary>
/// 描画処理
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(modelHandle);
}