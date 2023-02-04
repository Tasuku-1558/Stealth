#include "FirstStageMap.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const VECTOR FirstStageMap::SIZE	   = { 80.0f, 50.0f, 80.0f };						//モデルの倍率
const VECTOR FirstStageMap::POSITION   = { -2700.0f, -100.0f, -750.0f };				//モデルの位置
const VECTOR FirstStageMap::ROTATE     = { 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f };		//モデルの回転値

using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
FirstStageMap::FirstStageMap() : StageBase()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
FirstStageMap::~FirstStageMap()
{
	//終了処理が呼ばれてなければ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void FirstStageMap::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STAGE1));
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	position = POSITION;

	MV1SetPosition(modelHandle, position);

	//読み込み失敗でエラー
	if (modelHandle < 0)
	{
		printfDx("モデルデータ読み込みに失敗 [STAGE1]\n");
	}

	MapList();
}

/// <summary>
/// 終了処理
/// </summary>
void FirstStageMap::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

/// <summary>
/// 敵の行動パターンリスト
/// 左右移動の敵
/// </summary>
void FirstStageMap::MapList()
{
	positionList.push_back(VGet(-3200.0f, 100.0f, 1000.0f));
	positionList.push_back(VGet(-3200.0f, 100.0f, -1000.0f));

	itr = positionList.begin();   //  イテレータを先頭に設定
}

/// <summary>
/// 描画処理
/// </summary>
void FirstStageMap::Draw()
{
	MV1DrawModel(modelHandle);
}