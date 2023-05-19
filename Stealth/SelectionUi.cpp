#include "SelectionUi.h"
#include "Stage.h"
#include "InputManager.h"

char stage1[16][16] =
{
	1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
};

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
	, STAGE_SIZE({ 0.3f, 0.3f, 0.3f })
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
		{STAGE_DESCRIPTION_PATH},
		{SELECTION_KEY_PATH},
		{SELECTION_TITLE_PATH},
		{OPERATION_METHOD_PATH},
	};

	//セレクションUi画像の読み込み
	for (int i = 0; i < SELECTION_UI_NUMBER; i++)
	{
		selectionUiImage[i] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, ui[i].imagePath).c_str());
	}
	StagePop(stage1);

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
/// ステージ出現
/// </summary>
/// <param name="stageData">ステージのデータ</param>
void SelectionUi::StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_Z; i++)
	{
		for (int j = 0; j < BLOCK_NUM_X; j++)
		{
			stagePos.x = i * 100.0f;
			stagePos.z = (j * -100.0f) + 900.0f;

			if (stageData[j][i] == 0)
			{
				activeStage.emplace_back(new Stage(stagePos, STAGE_SIZE));
			}
		}
	}

	stagePos.y = STAGE_POS_Y;
}

/// <summary>
/// ステージのUi描画処理
/// </summary>
/// <param name="stageNumber">ステージの番号</param>
/// <param name="enemyNumber">敵の数</param>
/// <param name="cakeNumber">ケーキの数</param>
void SelectionUi::StageUiDraw(int stageNumber, int enemyNumber, int cakeNumber)
{
	DrawGraph(100, 150, selectionUiImage[0], TRUE);

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
	DrawRotaGraph(950, 550, 0.7, 0.0, selectionUiImage[2], TRUE);
}

/// <summary>
/// 描画処理
/// </summary>
void SelectionUi::Draw()
{
	DrawRotaGraph(500, 950, 0.85, 0.0, selectionUiImage[3], TRUE);

	DrawRotaGraph(1450, 950, 0.6, 0.0, selectionUiImage[1], TRUE);
}