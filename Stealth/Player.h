#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"

//プレイヤー状態
enum class PlayerState
{
	Nomal,
	Damage,
};

// プレイヤークラス
class Player final : public PlayerBase
{
public:
	 Player();		//コンストラクタ
	~Player();		//デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	int GetX() { return position.x; }
	int GetZ() { return position.z; }
	int GetHP() { return hp; }

	enum class PlayerState playerState;

private:
	Player(const Player&);			//コピーコンストラクタ

	void Move(float deltaTime);		//移動処理
	void pUpdate();


	int rightArmHandle;
	VECTOR rightArmPosition;


	static const VECTOR RIGHT_ARM_POSITION;
};