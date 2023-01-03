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
/// カーソルの状態
/// </summary>
enum class Cursor
{
	SELECTION,
	PUSH,
};

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


	enum class Cursor cursor;

private:
	Player(const Player&);							//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera);		//移動処理
	void Shoot(float deltaTime, Ball* ball);		//弾の発射処理
	void FoundEnemy(Enemy* enemy);					//エネミーに見つかった場合
	void aa(HitChecker* hitChecker);
	void cUpdate(Ball* ball);

	Bullet* bullet;

	int rightArmHandle;
	VECTOR rightArmPosition;

	static const VECTOR RIGHT_ARM_POSITION;
};