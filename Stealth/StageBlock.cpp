#include "StageBlock.h"
#include "ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">壁モデルの位置</param>
/// <param name="scale">壁モデルの大きさ</param>
StageBlock::StageBlock(VECTOR position, VECTOR scale)
{
	//壁モデルの読み込み
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE_BLOCK));

	//大きさと位置を設定
	MV1SetScale(modelHandle, scale);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// デストラクタ
/// </summary>
StageBlock::~StageBlock()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void StageBlock::Update(float deltaTime)
{
	//処理なし
}

/// <summary>
/// 描画処理
/// </summary>
void StageBlock::Draw()
{
	MV1DrawModel(modelHandle);
}