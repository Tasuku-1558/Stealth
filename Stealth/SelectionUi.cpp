#include "SelectionUi.h"


/// <summary>
/// コンストラクタ
/// </summary>
SelectionUi::SelectionUi()
	: fontHandle(0)
	, selectionKeyImage(0)
	, selectionUiImage(0)
	, stageDescription(0)
	, operationMethod(0)
	, modelHandle()
	, position()
	, IMAGE_FOLDER_PATH("Data/Image/")
	, SELECTION_KEY_PATH("selection_key.png")
	, SELECTION_TITLE_PATH("selection_Ui.png")
	, STAGE_DESCRIPTION_PATH("stage_description.png")
	, OPERATION_METHOD_PATH("operation_method.png")
	, STAGE_NUMBER(5)

	, STAGE1_POSITION({ 500.0f, 700.0f, 250.0f })
	, STAGE1_SIZE({ 14.0f, 14.0f, 14.0f })
	, STAGE1_ROTATE({ 0.0f, 180.0f * DX_PI_F / 180.0f, 15.0f * DX_PI_F / 180.0f })

	, STAGE2_POSITION({ -100.0f, 800.0f, 600.0f })
	, STAGE2_SIZE({ 11.0f, 11.0f, 11.0f })
	, STAGE2_ROTATE({ 80.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f })

	, STAGE3_POSITION({ 500.0f, 800.0f, 300.0f })
	, STAGE3_SIZE({ 10.0f, 10.0f, 10.0f })
	, STAGE3_ROTATE({ 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f })

	, STAGE4_POSITION({ 300.0f, 500.0f, 500.0f })
	, STAGE4_SIZE({ 11.0f, 11.0f, 11.0f })
	, STAGE4_ROTATE({ 0.0f, 180.0f * DX_PI_F / 180.0f, 5.0f * DX_PI_F / 180.0f })

	, STAGE5_POSITION({ -200.0f, 800.0f, 600.0f })
	, STAGE5_SIZE({ 13.0f, 13.0f, 13.0f })
	, STAGE5_ROTATE({ 0.0f, 180.0f * DX_PI_F / 180.0f, 5.0f * DX_PI_F / 180.0f })
{
	Initialize();
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
	//マップモデルの読み込み
	MapInput(0, ModelManager::STAGE1, STAGE1_POSITION, STAGE1_SIZE, STAGE1_ROTATE);

	MapInput(1, ModelManager::STAGE2, STAGE2_POSITION, STAGE2_SIZE, STAGE2_ROTATE);

	MapInput(2, ModelManager::STAGE3, STAGE3_POSITION, STAGE3_SIZE, STAGE3_ROTATE);

	MapInput(3, ModelManager::STAGE4, STAGE4_POSITION, STAGE4_SIZE, STAGE4_ROTATE);

	MapInput(4, ModelManager::STAGE5, STAGE5_POSITION, STAGE5_SIZE, STAGE5_ROTATE);


	//画像の読み込み
	stageDescription = LoadGraph(InputPath(IMAGE_FOLDER_PATH, STAGE_DESCRIPTION_PATH).c_str());

	selectionKeyImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SELECTION_KEY_PATH).c_str());

	selectionUiImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SELECTION_TITLE_PATH).c_str());

	operationMethod = LoadGraph(InputPath(IMAGE_FOLDER_PATH, OPERATION_METHOD_PATH).c_str());

	//フォントデータの作成
	fontHandle = CreateFontToHandle("Oranienbaum", 90, 1);
	
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

	DeleteGraph(selectionUiImage);

	//作成したフォントデータの削除
	DeleteFontToHandle(fontHandle);
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
	DrawFormatStringToHandle(370, 470, GetColor(255, 255, 255), fontHandle, "%d", enemyNumber);
	DrawFormatStringToHandle(520, 570, GetColor(255, 255, 255), fontHandle, "%d", cakeNumber);
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