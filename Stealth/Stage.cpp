#include "Stage.h"
#include "ModelManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelType"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
/// <param name="position"></param>
Stage::Stage(/*ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, */VECTOR position)
	: stageModel(0)
{
	/*modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);*/

	stageModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE));

	//壁モデルの位置を設定
	MV1SetPosition(stageModel, position);
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(stageModel);

	//MV1DeleteModel(modelHandle);
}

/// <summary>
/// 描画処理
/// </summary>
void Stage::Draw()
{
	//MV1DrawModel(modelHandle);

	MV1DrawModel(stageModel);
}