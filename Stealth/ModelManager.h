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
		PLAYER,
		PLAYER_ARM,
		ENEMY,
		WALL,
		BALL,
		STAGE1,
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
	 static const string PLAYER_BODY_PATH;		//player_bodyモデルファイルのパス
	 static const string PLAYER_ARM_PATH;		//player_armモデルファイルのパス
	 static const string ENEMY_BODY_PATH;		//enemy_bodyモデルファイルのパス
	 static const string WALL_PATH;				//wallモデルファイルのパス
	 static const string BALL_PATH;				//ballモデルファイルのパス
	 static const string STAGE1_PATH;			//stage1モデルファイルのパス

};