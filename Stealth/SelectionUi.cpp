#include "SelectionUi.h"


const string SelectionUi::IMAGE_FOLDER_PATH		  = "data/image/";				//imageフォルダまでのパス
const string SelectionUi::SELECTION_KEY_PATH	  = "selection_key.png";		//ステージセレクションUI画像のパス
const string SelectionUi::SELECTION_TITLE_PATH	  = "selection_Ui.png";			//ステージセレクションからタイトルへ遷移のUI画像
const string SelectionUi::STAGE_DESCRIPTION_PATH  = "stage_description.png";	//ステージの説明画像のパス
const string SelectionUi::OPERATION_METHOD_PATH	  = "operation_method.png";		//操作方法説明画像のパス
const int	 SelectionUi::STAGE_NUMBER			  = 4;							//ステージ数

const VECTOR SelectionUi::STAGE1_POSITION		  = { 1300.0f, 740.0f, 0.0f };		//ステージ1モデルの位置
const VECTOR SelectionUi::STAGE1_SIZE			  = { 10.0f, 10.0f, 10.0f };		//ステージ1モデルの倍率
const VECTOR SelectionUi::STAGE1_ROTATE = { 80.0f * DX_PI_F / 180.0f, 190.0f * DX_PI_F / 180.0f, 0.0f }; //ステージ1モデルの回転値

const VECTOR SelectionUi::STAGE2_POSITION		  = { 900.0f, 1050.0f, 0.0f };		//ステージ2モデルの位置
const VECTOR SelectionUi::STAGE2_SIZE			  = { 9.0f, 9.0f, 9.0f };			//ステージ2モデルの倍率
const VECTOR SelectionUi::STAGE2_ROTATE = { 80.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f }; //ステージ2モデルの回転値

const VECTOR SelectionUi::STAGE3_POSITION		  = { 1250.0f, 750.0f, -150.0f };	//ステージ3モデルの位置
const VECTOR SelectionUi::STAGE3_SIZE			  = { 7.0f, 7.0f, 7.0f };			//ステージ3モデルの倍率
const VECTOR SelectionUi::STAGE3_ROTATE = { 90.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }; //ステージ3モデルの回転値

const VECTOR SelectionUi::STAGE4_POSITION		  = { 1050.0f, 800.0f, -150.0f };	//ステージ4モデルの位置
const VECTOR SelectionUi::STAGE4_SIZE			  = { 6.0f, 6.0f, 6.0f };			//ステージ4モデルの倍率
const VECTOR SelectionUi::STAGE4_ROTATE = { 90.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }; //ステージ4モデルの回転値

const VECTOR SelectionUi::STAGE5_POSITION		  = { 750.0f, 950.0f, -150.0f };	//ステージ5モデルの位置
const VECTOR SelectionUi::STAGE5_SIZE			  = { 8.0f, 8.0f, 8.0f };			//ステージ5モデルの倍率
const VECTOR SelectionUi::STAGE5_ROTATE = { 90.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }; //ステージ5モデルの回転値


/// <summary>
/// コンストラクタ
/// </summary>
SelectionUi::SelectionUi()
	: font(0)
	, selectionKeyImage(0)
	, selectionUiImage(0)
	, stageDescription(0)
	, operationMethod(0)
	, modelHandle()
	, position()
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SelectionUi::~SelectionUi()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void SelectionUi::Initialize()
{
	//画像読み込み
	stageDescription  = LoadGraph(InputPath(IMAGE_FOLDER_PATH, STAGE_DESCRIPTION_PATH).c_str());

	selectionKeyImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SELECTION_KEY_PATH).c_str());

	selectionUiImage  = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SELECTION_TITLE_PATH).c_str());

	operationMethod	  = LoadGraph(InputPath(IMAGE_FOLDER_PATH, OPERATION_METHOD_PATH).c_str());

	//マップモデル読み込み
	MapInput(0, ModelManager::STAGE1, STAGE1_POSITION, STAGE1_SIZE, STAGE1_ROTATE);

	MapInput(1, ModelManager::STAGE2, STAGE2_POSITION, STAGE2_SIZE, STAGE2_ROTATE);

	MapInput(2, ModelManager::STAGE3, STAGE3_POSITION, STAGE3_SIZE, STAGE3_ROTATE);

	MapInput(3, ModelManager::STAGE4, STAGE4_POSITION, STAGE4_SIZE, STAGE4_ROTATE);

	MapInput(4, ModelManager::STAGE5, STAGE5_POSITION, STAGE5_SIZE, STAGE5_ROTATE);

	//フォントデータの作成
	font = CreateFontToHandle("Oranienbaum", 90, 1);

}

/// <summary>
/// マップ情報入力
/// </summary>
/// <param name="number"></param>
/// <param name="modelType"></param>
/// <param name="mapPos"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
void SelectionUi::MapInput(int number, ModelManager::ModelType modelType, VECTOR mapPos, VECTOR size, VECTOR rotate)
{
	modelHandle[number] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	position[number] = mapPos;
	MV1SetScale(modelHandle[number], size);
	MV1SetRotationXYZ(modelHandle[number], rotate);
	MV1SetPosition(modelHandle[number], position[number]);
}

/// <summary>
/// 画像のパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
std::string SelectionUi::InputPath(std::string folderPath, std::string imagePath)
{
	return std::string(folderPath + imagePath);
}

/// <summary>
/// 活性化処理
/// </summary>
void SelectionUi::Activate()
{

}

/// <summary>
/// 終了処理
/// </summary>
void SelectionUi::Finalize()
{
	for (int i = 0; i < STAGE_NUMBER; i++)
	{
		MV1DeleteModel(modelHandle[i]);
	}

	DeleteGraph(selectionKeyImage);

	DeleteGraph(stageDescription);

	DeleteGraph(operationMethod);

	//作成したフォントデータの削除
	DeleteFontToHandle(font);
}

/// <summary>
/// ステージのUI描画処理
/// </summary>
/// <param name="mapNumber"></param>
/// <param name="enemyNumber"></param>
/// <param name="cakeNumber"></param>
void SelectionUi::StageUiDraw(int mapNumber, int enemyNumber, int cakeNumber)
{
	DrawGraph(100, 150, stageDescription, TRUE);
	MV1DrawModel(modelHandle[mapNumber]);

	//敵とケーキの数を表示
	DrawFormatStringToHandle(370, 470, GetColor(255, 255, 255), font, "%d", enemyNumber);
	DrawFormatStringToHandle(520, 570, GetColor(255, 255, 255), font, "%d", cakeNumber);
}

/// <summary>
/// タイトルへ遷移するUI描画処理
/// </summary>
void SelectionUi::TitleUiDraw()
{
	DrawRotaGraph(950, 550, 0.7f, 0, selectionUiImage, TRUE);
}

/// <summary>
/// 描画処理
/// </summary>
void SelectionUi::Draw()
{
	DrawRotaGraph(500, 950, 0.85f, 0, operationMethod, TRUE);

	DrawRotaGraph(1450, 950, 0.6f, 0, selectionKeyImage, TRUE);
}