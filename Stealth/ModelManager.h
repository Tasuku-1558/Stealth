#pragma once

#include <string>

using namespace std;

/// <summary>
/// シングルトン
/// モデル管理クラス
/// </summary>
class ModelManager final
{
public:

	//モデルの種類
	enum ModelType
	{
		PLAYER,			//プレイヤーモデル
		ENEMY,			//エネミーモデル
		ENEMY_VISUAL,	//エネミーの視野モデル
		CAKE,			//ケーキモデル
		CAKE_HALF,		//ケーキが半分のモデル
		STAGE1,			//ステージ1モデル
		STAGE2,			//ステージ2モデル
		STAGE3,			//ステージ3モデル
		STAGE4,			//ステージ4モデル
		STAGE5,			//ステージ5モデル
		GOAL,			//ゴールフラッグモデル
		MODEL_AMOUNT	//モデルの個数
	};

	static ModelManager& GetInstance();					  //アドレスを返す

	const int& GetModelHandle(ModelType modelType) const; //モデルハンドルの参照を返す

private:
	ModelManager();
	ModelManager(const ModelManager&);			//コピーコンストラクタ
	virtual ~ModelManager();

	string InputPath(string folderPath,			//モデルのパスを入力
					 string modelPath);

	void LoadAllModel();						//全てのモデルの読み込み
	void DeleteAllModel();						//全てのモデルの削除

	int modelHandle[MODEL_AMOUNT];				//モデルハンドル

	//定数
	const string MODEL_FOLDER_PATH;	//modelフォルダまでのパス
	const string PLAYER_PATH;		//playerモデルファイルのパス
	const string ENEMY_PATH;		//enemyモデルファイルのパス
	const string ENEMY_VISUAL_PATH;	//enemy_visualモデルファイルのパス
	const string CAKE_PATH;			//cakeモデルファイルのパス
	const string CAKE_HALF_PATH;	//cake_halfモデルファイルのパス
	const string STAGE1_PATH;		//stage1モデルファイルのパス
	const string STAGE2_PATH;		//stage2モデルファイルのパス
	const string STAGE3_PATH;		//stage3モデルファイルのパス
	const string STAGE4_PATH;		//stage4モデルファイルのパス
	const string STAGE5_PATH;		//stage5モデルファイルのパス
	const string GOAL_FLAG_PATH;	//goal_flagモデルファイルのパス

};