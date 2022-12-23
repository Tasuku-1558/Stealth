#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

class Camera;
class Bullet;
class Boal;

/// <summary>
/// プレイヤー状態
/// </summary>
enum class PlayerState
{
	Nomal,
};

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final : public PlayerBase
{
public:
	 Player();		//コンストラクタ
	~Player();		//デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Camera* camera, Boal* boal);
	void Draw();

	/*VECTOR GetUp() { return UP; }
	VECTOR GetDown() { return DOWN; }
	VECTOR GetLeft() { return LEFT; }
	VECTOR GetRight() { return RIGHT; }*/

	//デバック用
	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetFind() { return foundTimes; }
	int GetSpeed() { return SPEED; }


	enum class PlayerState playerState;

private:
	Player(const Player&);			//コピーコンストラクタ

	void Move(float deltaTime, Camera* camera);		//移動処理
	void Shoot(float deltaTime, Boal* boal);							//弾の発射処理
	void pUpdate();

	Bullet* bullet;

	int rightArmHandle;
	VECTOR rightArmPosition;
	bool boalGet;


	static const VECTOR RIGHT_ARM_POSITION;
};