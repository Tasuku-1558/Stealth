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
		STONE,			//小石モデル
		STAGE,			//ステージモデル
		GOAL,			//ゴールフラッグモデル
		MODEL_AMOUNT,	//モデルの数
	};

	static ModelManager& GetInstance();					  //アドレスを返す

	const int& GetModelHandle(ModelType modelType) const; //モデルハンドルの参照を返す

private:
	ModelManager();
	ModelManager(const ModelManager&);		//コピーコンストラクタ
	virtual ~ModelManager();

	void LoadAllModel();		//全てのモデルの読み込み
	void DeleteAllModel();		//全てのモデルの削除

	struct Model
	{
		string modelPath;		//モデルのパス
	};

	int modelHandle[MODEL_AMOUNT];	//モデルハンドル

	//定数
	const string MODEL_FOLDER_PATH;	//Modelフォルダまでのパス
	const string PLAYER_PATH;		//playerモデルファイルのパス
	const string ENEMY_PATH;		//enemyモデルファイルのパス
	const string ENEMY_VISUAL_PATH;	//enemy_visualモデルファイルのパス
	const string CAKE_PATH;			//cakeモデルファイルのパス
	const string CAKE_HALF_PATH;	//cake_halfモデルファイルのパス
	const string STONE_PATH;		//stoneモデルファイルのパス
	const string STAGE_PATH;		//stageモデルファイルのパス
	const string GOAL_FLAG_PATH;	//goal_flagモデルファイルのパス
};