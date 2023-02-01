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

	ModelManager();
	~ModelManager();

	//モデルの種類
	enum ModelType
	{
		PLAYER,			//プレイヤーモデル
		ENEMY,			//エネミーモデル
		ENEMY_VISUAL,	//エネミーの視野モデル
		WALL,			//壁モデル
		CAKE,			//ケーキモデル
		STAGE1,			//ステージ1モデル
		STAGE2,			//ステージ2モデル
		STAGE3,			//ステージ3モデル
		MODEL_AMOUNT	//モデルの個数
	};

	static ModelManager& GetInstance();					  //アドレスを返す

	const int& GetModelHandle(ModelType modelType) const; //モデルハンドルの参照を返す

private:

	 ModelManager(const ModelManager&);			//コピーコンストラクタ

	 string InputPath(string folderPath,	//モデルのパスを入力
					  string path);

	 void LoadAllModel();						//全てのモデルの読み込み
	 void DeleteAllModel();						//全てのモデルの削除


	 int modelHandle[MODEL_AMOUNT];				//モデルハンドル

	 //静的定数
	 static const string MODEL_FOLDER_PATH;		//modelフォルダまでのパス
	 static const string PLAYER_PATH;			//playerモデルファイルのパス
	 static const string ENEMY_PATH;			//enemyモデルファイルのパス
	 static const string ENEMY_VISUAL_PATH;		//enemy_visualモデルファイルのパス
	 static const string WALL_PATH;				//wallモデルファイルのパス
	 static const string CAKE_PATH;				//cakeモデルファイルのパス
	 static const string STAGE1_PATH;			//stage1モデルファイルのパス
	 static const string STAGE2_PATH;			//stage2モデルファイルのパス
	 static const string STAGE3_PATH;			//stage3モデルファイルのパス

};