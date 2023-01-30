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
	void Update(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//更新処理
	void FoundEnemy(Enemy* enemy);												//エネミーに見つかった場合
	void Draw();																//描画処理


	//デバック用
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }


private:
	Player(const Player&);														//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit);		//移動処理
	int count;
};