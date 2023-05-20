#pragma once

#include <string>
#include <vector>
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "Stage.h"

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

	Stage* stage;
	vector<Stage*> activeStage;

	void Initialize();			//初期化処理
	void Finalize();			//終了処理
	void StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X]);		//ステージの出現

	struct Ui
	{
		string imagePath;		//Ui画像のパス
	};

	int fontHandle;				//ゲームフォント
	int selectionUiImage[4];	//セレクションUi画像の格納用
	VECTOR stagePos;			//ステージの座標

	//定数
	const int	 SELECTION_UI_NUMBER;		//セレクションUi画像の数
	const int	 SELECTION_FONT_SIZE;		//ゲームフォントのサイズ
	const int	 FONT_THICK;				//フォントの太さ
	const int	 STAGE_NUMBER;				//ステージ数

	const float  STAGE_POS_Y;				//ステージのY座標

	const VECTOR STAGE_SIZE;				//ステージのサイズ

	const string IMAGE_FOLDER_PATH;			//Imageフォルダまでのパス
	const string SELECTION_KEY_PATH;		//ステージセレクションUi画像のパス
	const string SELECTION_TITLE_PATH;		//ステージセレクションからタイトルへ遷移のUi画像
	const string STAGE_DESCRIPTION_PATH;	//ステージの説明画像のパス
	const string OPERATION_METHOD_PATH;		//操作方法説明画像のパス
};