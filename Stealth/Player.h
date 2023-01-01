#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

class Camera;
class Bullet;
class Boal;
class Enemy;


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
	~Player();		//デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, Boal* boal, Enemy* enemy);
	void Draw();
	bool Geta() { return a; }

	//デバック用
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetFind() { return foundTimes; }
	int GetSpeed() { return SPEED; }


	enum class Cursor cursor;

private:
	Player(const Player&);							//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera);		//移動処理
	void Shoot(float deltaTime, Boal* boal);		//弾の発射処理
	void FoundEnemy(Enemy* enemy);					//エネミーに見つかる
	void cUpdate(Boal* boal);

	Bullet* bullet;

	int rightArmHandle;
	VECTOR rightArmPosition;
	int count;
	bool a;

	static const VECTOR RIGHT_ARM_POSITION;
};