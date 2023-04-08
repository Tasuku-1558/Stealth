#include "Stage.h"


char stage1[16][16] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
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
	: kabe(0)
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	MV1SetScale(modelHandle, size);
	MV1SetRotationXYZ(modelHandle, rotate);
	MV1SetPosition(modelHandle, position);

	kabe = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::KABE));
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
	MV1DeleteModel(kabe);
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 描画処理
/// </summary>
void Stage::Draw()
{
	MV1DrawModel(modelHandle);

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			//道ではないところは描画しない
			if (stage1[i][j] == 0) continue;

			//壁モデルの位置を設定
			MV1SetPosition(kabe, VGet(j * 1000.0f, 0.0f, i * 1000.0f));

			//４方の壁の状態で描画するフレーム番号を変更する
			int FrameNo = 0;
			if (stage1[i][j + 1] == 0) FrameNo += 1;
			if (stage1[i][j - 1] == 0) FrameNo += 2;
			if (stage1[i + 1][j] == 0) FrameNo += 4;
			if (stage1[i - 1][j] == 0) FrameNo += 8;

			//割り出した番号のフレームを描画する
			MV1DrawFrame(kabe, FrameNo);
		}
	}
}