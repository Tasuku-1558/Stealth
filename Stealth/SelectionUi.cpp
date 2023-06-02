#include "SelectionUi.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
SelectionUi::SelectionUi()
	: fontHandle(0)
	, selectionUiImage()
	, stagePos()
	, SELECTION_UI_NUMBER(4)
	, SELECTION_FONT_SIZE(90)
	, FONT_THICK(1)
	, STAGE_NUMBER(2)
	, STAGE_POS_Y(150.0f)
	, BLOCK_SIZE({ 0.3f, 0.3f, 0.3f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, SELECTION_KEY_PATH("selection_key.png")
	, SELECTION_TITLE_PATH("selection_Ui.png")
	, STAGE_DESCRIPTION_PATH("stage_description.png")
	, OPERATION_METHOD_PATH("operation_method.png")
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
	Ui ui[] =
	{
		{SELECTION_KEY_PATH},
		{SELECTION_TITLE_PATH},
		{STAGE_DESCRIPTION_PATH},
		{OPERATION_METHOD_PATH},
	};

	//セレクションUi画像の読み込み
	for (int i = 0; i < SELECTION_UI_NUMBER; i++)
	{
		selectionUiImage[i] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, ui[i].imagePath).c_str());
	}

	StageList stageList[] =
	{
		{1, "Data/Csv/Stage1.csv"},
		{2, "Data/Csv/Stage2.csv"},
		{3, "Data/Csv/Stage1.csv"},
		{4, "Data/Csv/Stage1.csv"},
		{5, "Data/Csv/Stage1.csv"},
	};

	//CSVファイルの読み込み
	for (int i = 0; i < MAX_STAGE_NUMBER; i++)
	{
		stageData = new StageData(stageList[i].csvName);
	}

	StagePop();

	//フォントデータの作成
	fontHandle = CreateFontToHandle("Oranienbaum", SELECTION_FONT_SIZE, FONT_THICK);
}

/// <summary>
/// 終了処理
/// </summary>
void SelectionUi::Finalize()
{
	for (int i = 0; i < SELECTION_UI_NUMBER; i++)
	{
		DeleteGraph(selectionUiImage[i]);
	}

	//作成したフォントデータの削除
	DeleteFontToHandle(fontHandle);
}

/// <summary>
/// ステージの出現
/// </summary>
void SelectionUi::StagePop()
{
	stagePos.y = STAGE_POS_Y;

	for (int i = 0; i < BLOCK_NUM; i++)
	{
		for (int j = 0; j < BLOCK_NUM; j++)
		{
			stagePos.x = i * 100.0f;
			stagePos.z = (j * -100.0f) + 900.0f;

			if (stageData->stageNum[j * BLOCK_NUM + i] == 0)
			{
				activeStage.emplace_back(new StageBlock(stagePos, BLOCK_SIZE));
			}
		}
	}
}

/// <summary>
/// ステージのUi描画処理
/// </summary>
/// <param name="stageNumber">ステージの番号</param>
/// <param name="enemyNumber">敵の数</param>
/// <param name="cakeNumber">ケーキの数</param>
void SelectionUi::StageUiDraw(int stageNumber, int enemyNumber, int cakeNumber)
{
	DrawGraph(100, 150, selectionUiImage[Image::DESCRIPTION], TRUE);

	//敵とケーキの数を表示
	DrawFormatStringToHandle(370, 470, GetColor(255, 255, 255), fontHandle, "%d", enemyNumber);
	DrawFormatStringToHandle(520, 570, GetColor(255, 255, 255), fontHandle, "%d", cakeNumber);

	for (auto itr = activeStage.begin(); itr != activeStage.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

/// <summary>
/// タイトルへ遷移するUi描画処理
/// </summary>
void SelectionUi::TitleUiDraw()
{
	DrawRotaGraph(950, 550, 0.7, 0.0, selectionUiImage[Image::TITLE], TRUE);
}

/// <summary>
/// 描画処理
/// </summary>
void SelectionUi::Draw()
{
	DrawRotaGraph(500, 950, 0.85, 0.0, selectionUiImage[Image::OPERATION_METHOD], TRUE);

	DrawRotaGraph(1450, 950, 0.6, 0.0, selectionUiImage[Image::KEY], TRUE);
}