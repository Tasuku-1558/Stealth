#pragma once

#include "DxLib.h"
#include "ModelManager.h"
#include <string>

using namespace std;

/// <summary>
/// ステージ選択画面用Uiクラス
/// </summary>
class SelectionUi final
{
public:
	SelectionUi();
	virtual ~SelectionUi();

	void Draw();		//描画処理
	void StageUiDraw(int mapNumber, int enemyNumber, 
					 int cakeNumber);		//ステージのUi描画処理

	void TitleUiDraw();		//タイトルへ遷移するUi描画処理

private:
	SelectionUi(const SelectionUi&);	//コピーコンストラクタ

	void Initialize();			//初期化処理
	void Finalize();			//終了処理

	void MapInput(int number, ModelManager::ModelType modelType, 
				  VECTOR mapPos, VECTOR size, VECTOR rotate);		//マップ情報入力

	int fontHandle;				//ゲームフォント
	int selectionKeyImage;		//ステージセレクションUi画像
	int selectionUiImage;		//ステージセレクションからタイトルへ遷移のUi画像
	int stageDescription;		//ステージの説明画像ハンドル
	int operationMethod;		//操作方法説明画像のハンドル
	int modelHandle[2];			//マップモデルハンドル
	VECTOR position[2];			//マップモデルの位置

	//定数
	const int	 SELECTION_FONT_SIZE;		//ゲームフォントのサイズ
	const int	 FONT_THICK;				//フォントの太さ
	const int	 STAGE_NUMBER;				//ステージ数

	const VECTOR STAGE1_POSITION;			//ステージ1モデルの位置
	const VECTOR STAGE1_SIZE;				//ステージ1モデルの倍率
	const VECTOR STAGE1_ROTATE;				//ステージ1モデルの回転値

	const VECTOR STAGE2_POSITION;			//ステージ2モデルの位置
	const VECTOR STAGE2_SIZE;				//ステージ2モデルの倍率
	const VECTOR STAGE2_ROTATE;				//ステージ2モデルの回転値

	const string IMAGE_FOLDER_PATH;			//Imageフォルダまでのパス
	const string SELECTION_KEY_PATH;		//ステージセレクションUi画像のパス
	const string SELECTION_TITLE_PATH;		//ステージセレクションからタイトルへ遷移のUi画像
	const string STAGE_DESCRIPTION_PATH;	//ステージの説明画像のパス
	const string OPERATION_METHOD_PATH;		//操作方法説明画像のパス
};