#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"

class Enemy;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player();
	 virtual ~Player();

	void Initialize();															//初期化処理
	void Finalize();															//終了処理
	void Activate();															//活性化処理

	void Update(float deltaTime, Camera* camera, 
				VECTOR back, bool mapHit);										//更新処理

	void FoundEnemy(float deltaTime, Enemy* enemy);								//エネミーに見つかった場合
	void Draw();																//描画処理

	const int GetPlayerCount() { return playerFindCount; }						//エネミーに見つかった回数を返す


	//デバック用
	float GetSpeed() { return SPEED; }


private:
	Player(const Player&);														//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//移動処理

	float initialCount;		//初期位置に戻すカウント
	int emptyModel;
	VECTOR pastPosition;
	float count;

	//静的定数
	static const std::string SOUND_FOLDER_PATH;		//soundフォルダまでのパス
	static const std::string SPOTTED_SE_PATH;		//エネミーに見つかった時のSE音のパス

};