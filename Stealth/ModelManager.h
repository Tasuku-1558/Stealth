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
		WALL,			//壁モデル
		BALL,			//ボールモデル
		STAGE1,			//ステージ1モデル
		STAGE2,			//ステージ2モデル
		MODEL_AMOUNT	//モデルの個数
	};

	static ModelManager& GetInstance();					  // アドレスを返す

	const int& GetModelHandle(ModelType modelType) const; // モデルハンドルの参照を返す

private:

	 ModelManager();							//コンストラクタ
	~ModelManager();							//デストラクタ

	 ModelManager(const ModelManager&);			//コピーコンストラクタ

	 void LoadAllModel();						//全てのモデルの読み込み
	 void DeleteAllModel();						//全てのモデルの削除


	 int modelHandle[MODEL_AMOUNT];				//モデルハンドル

	 //静的定数
	 static const string MODEL_FOLDER_PATH;		//modelフォルダまでのパス
	 static const string PLAYER_PATH;			//playerモデルファイルのパス
	 static const string ENEMY_PATH;			//enemyモデルファイルのパス
	 static const string WALL_PATH;				//wallモデルファイルのパス
	 static const string BALL_PATH;				//ballモデルファイルのパス
	 static const string STAGE1_PATH;			//stage1モデルファイルのパス
	 static const string STAGE2_PATH;			//stage2モデルファイルのパス
};