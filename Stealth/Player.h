#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"


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

private:
	Player(const Player&);			//コピーコンストラクタ

	void Move(float deltaTime);		//移動処理

	int rightArmHandle;
	VECTOR rightArmPosition;
	static const VECTOR RIGHT_ARM_POSITION;
};