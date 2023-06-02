#pragma once

#include "StageBlock.h"
#include "StageData.h"

using namespace std;

/// <summary>
/// ステージ選択画面用Uiクラス
/// </summary>
class SelectionUi final
{
public:
	SelectionUi();
	virtual ~SelectionUi();

	void Draw();						//描画処理

	void StageUiDraw(int stageNumber,
					 int enemyNumber,
					 int cakeNumber);	//ステージのUi描画処理

	void TitleUiDraw();					//タイトルへ遷移するUi描画処理

private:
	SelectionUi(const SelectionUi&);	//コピーコンストラクタ

	StageBlock* stageBlock;
	StageData* stageData;
	vector<StageBlock*> activeStage;

	void Initialize();		//初期化処理
	void Finalize();		//終了処理
	void StagePop();		//ステージの出現

	//セレクションUi画像の種類
	enum Image
	{
		KEY,				//キー操作の画像
		TITLE,				//タイトルへ遷移する説明画像
		DESCRIPTION,		//ステージの説明画像
		OPERATION_METHOD,	//ゲーム操作説明画像
		IMAGE_AMOUNT,		//セレクションUi画像の数
	};

	struct Ui
	{
		string imagePath;	//Ui画像のパス
	};

	struct StageList
	{
		int number;
		char csvName[20];	//Csvファイルの名前
	};

	int fontHandle;						//ゲームフォント
	int selectionUiImage[IMAGE_AMOUNT];	//セレクションUi画像の格納用
	VECTOR stagePos;					//ステージの座標

	//定数
	const int	 SELECTION_UI_NUMBER;		//セレクションUi画像の数
	const int	 SELECTION_FONT_SIZE;		//ゲームフォントのサイズ
	const int	 FONT_THICK;				//フォントの太さ
	const int	 STAGE_NUMBER;				//ステージ数

	const float  STAGE_POS_Y;				//ステージのY座標

	const VECTOR BLOCK_SIZE;				//ブロックのサイズ

	const string IMAGE_FOLDER_PATH;			//Imageフォルダまでのパス
	const string SELECTION_KEY_PATH;		//キー操作の画像のパス
	const string SELECTION_TITLE_PATH;		//ステージセレクションからタイトルへ遷移の画像のパス
	const string STAGE_DESCRIPTION_PATH;	//ステージの説明画像のパス
	const string OPERATION_METHOD_PATH;		//操作方法説明画像のパス
};