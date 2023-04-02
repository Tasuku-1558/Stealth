#include "CakeParticle.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="particlePosition">パーティクルの位置</param>
CakeParticle::CakeParticle(const VECTOR& particlePosition)
	: PINK(GetColor(224, 148, 171))
	, PARTICLE_POP_TIME(2.0f)
	, POS_Y(0.0f)
{
	position = particlePosition;

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
CakeParticle::~CakeParticle()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void CakeParticle::Initialize()
{
	//パーティクルを飛ばす力をランダム値にする
	float rad = (float)(rand() % 200) / 100.0f;
	float tmpRadius = (float)(rand() % 100) / 10.0f;

	xPower = tmpRadius * cosf(rad * DX_PI_F);
	zPower = tmpRadius * sinf(rad * DX_PI_F);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void CakeParticle::Update(float deltaTime)
{
	//パーティクルの半径を調整する
	radius = ((PARTICLE_POP_TIME - particleCount) / PARTICLE_POP_TIME) * radius;

	//パーティクルに飛ばす力を加える
	position.x += xPower;
	position.y = POS_Y;
	position.z += zPower;
	
	//パーティクルを出したらカウントを開始する
	particleCount += deltaTime;

	//パーティクルの出現時間を超えたらパーティクルを消す
	if (particleCount > PARTICLE_POP_TIME)
	{
		endFlag = true;

		particleCount = 0.0f;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void CakeParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(position, radius, DIVNUM, PINK, PINK, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}