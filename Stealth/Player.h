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
	 Player();				//コンストラクタ
	 virtual ~Player();		//デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, bool mapHit);
	void EnemyUpdate(Enemy* enemy);
	void Draw();


	//デバック用
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }


private:
	Player(const Player&);								//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera, bool mapHit);			//移動処理
	void FoundEnemy(Enemy* enemy);						//エネミーに見つかった場合
	void aio(bool mapHit);

};