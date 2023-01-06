#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

class Camera;
class Bullet;
class Ball;
class Enemy;
class HitChecker;


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
	void Update(float deltaTime, Camera* camera, Ball* ball, Enemy* enemy, HitChecker* hitChecker);
	void Draw();


	//デバック用
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetSpeed() { return SPEED; }


private:
	Player(const Player&);							//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera, HitChecker* hitChecker);		//移動処理
	void Shoot(float deltaTime, Ball* ball);		//弾の発射処理
	void FoundEnemy(Enemy* enemy);					//エネミーに見つかった場合
	void aa(HitChecker* hitChecker);

	Bullet* bullet;

	int rightArmHandle;
	VECTOR rightArmPosition;

	float bulletCount;

	static const VECTOR RIGHT_ARM_POSITION;
};