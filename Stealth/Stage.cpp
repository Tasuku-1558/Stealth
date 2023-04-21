#include "Stage.h"


char stage1[16][16] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelType"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
/// <param name="position"></param>
Stage::Stage(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position)
	: stageModel(0)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);

	stageModel = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE));
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
	Finalize();
}

/// <summary>
/// 終了処理
/// </summary>
void Stage::Finalize()
{
	MV1DeleteModel(stageModel);

	MV1DeleteModel(modelHandle);
}

void Stage::Update()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			//壁モデルの位置を設定
			MV1SetPosition(stageModel, VGet(j * 1.0f, 0.0f, i * 1.0f));
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(modelHandle);

	MV1DrawModel(stageModel);
}