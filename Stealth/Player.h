#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"

using namespace std;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player();
	 virtual ~Player();

	void Initialize();															//初期化処理
	void Activate();															//活性化処理

	void Update(float deltaTime, Camera* camera, 
				VECTOR back, bool mapHit);										//更新処理

	void FoundEnemy(float deltaTime, bool spotted);								//エネミーに見つかった場合
	void Draw();																//描画処理

	const int GetPlayerCount() { return playerFindCount; }						//エネミーに見つかった回数を返す


private:
	Player(const Player&);														//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//移動処理
	void Finalize();															//終了処理
	void AfterImage();															//プレイヤーの残像処理
	void HitMap(VECTOR back, bool mapHit);										//マップに衝突した
	string InputPath(string folderPath,											//パスを入力
					 string path);

	float initialCount;			//初期位置に戻すカウント
	int emptyModel[12];			//残像モデル格納用
	VECTOR pastPosition[12];	//プレイヤーの過去の位置

	//定数
	const string IMAGE_FOLDER_PATH;		//imageフォルダまでのパス
	const string PLAYER_FIND_PATH;		//エネミーに見つかった時の画像のパス
	const int	 AFTER_IMAGE_NUMBER;	//プレイヤーの残像枚数
};