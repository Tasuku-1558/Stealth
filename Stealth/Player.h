#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Camera.h"
#include "Ball.h"

class Enemy;
class Bullet;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player(Object PLAYER);		//コンストラクタ
	~Player();					//デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, Ball* ball, Enemy* enemy);
	void Draw();

	VECTOR GetBulletPos() { return bulletPosition; }

	//デバック用
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }


private:
	Player(const Player&);								//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera);			//移動処理
	void Shoot(float deltaTime, Ball* ball);			//弾の発射処理
	void FoundEnemy(Enemy* enemy);						//エネミーに見つかった場合
	void BulletReuse(float deltaTime, Ball* ball);		//バレット再使用カウント


	Bullet* bullet;

	float bulletCount;				//弾の効果時間
	VECTOR bulletPosition;			//弾の位置
};