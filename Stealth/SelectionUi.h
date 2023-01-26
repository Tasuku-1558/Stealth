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

	void Initialize();								//初期化処理
	void Activate();
	void Finalize();								//終了処理
	void Draw();									//描画処理
	void Stage1_Draw();								//ステージ1のUI描画処理
	void Stage2_Draw();								//ステージ2のUI描画処理

private:
	SelectionUi(const SelectionUi&);				//コピーコンストラクタ
	void MapInput(int number, ModelManager::ModelType modelType, VECTOR mapPos, VECTOR size, VECTOR rotate);	//マップ情報入力


	int selectionKeyImage;							//ステージセレクションUI画像
	int stageDescription[2];						//ステージの説明画像ハンドル
	int modelHandle[2];								//マップモデルハンドル
	VECTOR position[2];								//マップモデルの位置


	//静的定数
	static const string IMAGE_FOLDER_PATH;			//imageフォルダまでのパス
	static const string SELECTION_KEY_PATH;			//ステージセレクションUI画像のパス
	static const string STAGE1_DESCRIPTION_PATH;	//ステージ1の説明画像のパス
	static const string STAGE2_DESCRIPTION_PATH;	//ステージ2の説明画像のパス
	static const int	STAGE_NUMBER;				//ステージ数

	static const VECTOR STAGE1_POSITION;			//ステージ1モデルの位置
	static const VECTOR STAGE1_SIZE;				//ステージ1モデルの倍率
	static const VECTOR STAGE1_ROTATE;				//ステージ1モデルの回転値

	static const VECTOR STAGE2_POSITION;			//ステージ2モデルの位置
	static const VECTOR STAGE2_SIZE;				//ステージ2モデルの倍率
	static const VECTOR STAGE2_ROTATE;				//ステージ2モデルの回転値

};