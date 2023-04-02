#include "FireWorksParticle.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="particlePosition">パーティクルの位置</param>
/// <param name="particleColor">パーティクルの色</param>
FireWorksParticle::FireWorksParticle(const VECTOR particlePosition, unsigned int particleColor)
	: color(0)
	, PARTICLE_POP_TIME(3.0f)
	, POS_Y(1000.0f)
{
	position = particlePosition;

	color = particleColor;

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
FireWorksParticle::~FireWorksParticle()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void FireWorksParticle::Initialize()
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
void FireWorksParticle::Update(float deltaTime)
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
void FireWorksParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(position, radius, DIVNUM, color, color, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}