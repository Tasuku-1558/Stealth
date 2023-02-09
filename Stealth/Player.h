#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"


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


	//デバック用
	float GetSpeed() { return SPEED; }


private:
	Player(const Player&);														//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//移動処理
	void Finalize();															//終了処理
	void AfterImage(float deltaTime);											//プレイヤーの残像

	float initialCount;			//初期位置に戻すカウント
	int emptyModel[3];
	VECTOR pastPosition[3];
	float count;

	//静的定数
	static const std::string SOUND_FOLDER_PATH;		//soundフォルダまでのパス
	static const std::string SPOTTED_SE_PATH;		//エネミーに見つかった時のSE音のパス
	static const int		 AFTER_IMAGE_NUMBER;	//プレイヤーの残像枚数
};