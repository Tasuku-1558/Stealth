#include "Wall.h"
#include "ModelManager.h"


const VECTOR Wall::SIZE		= { 2.0f, 2.0f, 2.0f };		//モデルの倍率
const VECTOR Wall::POSITION = { -2500.0f,30.0f,0.0f };	//モデルの位置


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos"></param>
Wall::Wall(VECTOR pos)
{
	position = pos;
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Wall::~Wall()
{
	// 終了処理が呼ばれていなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void Wall::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::WALL));
	MV1SetScale(modelHandle, SIZE);

	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [WALL]\n");
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Wall::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// 描画処理
/// </summary>
void Wall::Draw()
{
	MV1DrawModel(modelHandle);
}