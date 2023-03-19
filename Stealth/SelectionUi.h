#pragma once

#include "DxLib.h"
#include "ModelManager.h"
#include <string>

using namespace std;

/// <summary>
/// ステージ選択画面用UIクラス
/// </summary>
class SelectionUi final
{
public:

	SelectionUi();
	virtual ~SelectionUi();

	void Draw();									//描画処理
	void StageUiDraw(int mapNumber, int enemyNumber, 
					 int cakeNumber);				//ステージのUI描画処理

	void TitleUiDraw();								//タイトルへ遷移するUI描画処理

private:
	SelectionUi(const SelectionUi&);				//コピーコンストラクタ

	void Initialize();								//初期化処理
	void Finalize();								//終了処理

	void MapInput(int number, ModelManager::ModelType modelType, 
				  VECTOR mapPos, VECTOR size, VECTOR rotate);		//マップ情報入力

	string InputPath(string folderPath,				//画像のパスを入力
					 string imagePath);

	int fontHandle;										//ゲームフォント
	int selectionKeyImage;							//ステージセレクションUI画像
	int selectionUiImage;							//ステージセレクションからタイトルへ遷移のUI画像
	int stageDescription;							//ステージの説明画像ハンドル
	int operationMethod;							//操作方法説明画像のハンドル
	int modelHandle[5];								//マップモデルハンドル
	VECTOR position[5];								//マップモデルの位置

	//定数
	const string IMAGE_FOLDER_PATH;			//imageフォルダまでのパス
	const string SELECTION_KEY_PATH;		//ステージセレクションUI画像のパス
	const string SELECTION_TITLE_PATH;		//ステージセレクションからタイトルへ遷移のUI画像
	const string STAGE_DESCRIPTION_PATH;	//ステージの説明画像のパス
	const string OPERATION_METHOD_PATH;		//操作方法説明画像のパス
	const int	 STAGE_NUMBER;				//ステージ数

	const VECTOR STAGE1_POSITION;			//ステージ1モデルの位置
	const VECTOR STAGE1_SIZE;				//ステージ1モデルの倍率
	const VECTOR STAGE1_ROTATE;				//ステージ1モデルの回転値

	const VECTOR STAGE2_POSITION;			//ステージ2モデルの位置
	const VECTOR STAGE2_SIZE;				//ステージ2モデルの倍率
	const VECTOR STAGE2_ROTATE;				//ステージ2モデルの回転値

	const VECTOR STAGE3_POSITION;			//ステージ3モデルの位置
	const VECTOR STAGE3_SIZE;				//ステージ3モデルの倍率
	const VECTOR STAGE3_ROTATE;				//ステージ3モデルの回転値

	const VECTOR STAGE4_POSITION;			//ステージ4モデルの位置
	const VECTOR STAGE4_SIZE;				//ステージ4モデルの倍率
	const VECTOR STAGE4_ROTATE;				//ステージ4モデルの回転値

	const VECTOR STAGE5_POSITION;			//ステージ5モデルの位置
	const VECTOR STAGE5_SIZE;				//ステージ5モデルの倍率
	const VECTOR STAGE5_ROTATE;				//ステージ5モデルの回転値

};