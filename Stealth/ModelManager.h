#pragma once

#include <string>

using namespace std;

//シングルトン
//モデル管理クラス
class ModelManager final
{
public:

	//モデルの種類
	enum ModelType
	{
		PLAYER_BODY,
		PLAYER_ARM,
		ENEMY_BODY,
		BLOCK,
		BOAL,
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

	 //静的定数
	 static const string MODEL_FOLDER_PATH;		//modelフォルダまでのパス
	 static const string PLAYER_BODY_PATH;		//player_bodyモデルファイルのパス
	 static const string PLAYER_ARM_PATH;		//player_armモデルファイルのパス
	 static const string ENEMY_BODY_PATH;		//enemy_bodyモデルファイルのパス
	 static const string BOAL_PATH;				//boalモデルファイルのパス

	 //デバック用
	 static const string BLOCK_PATH;

	 int modelHandle[MODEL_AMOUNT];				//モデルハンドル
};