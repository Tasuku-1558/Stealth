#include "CakeParticle.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pos"></param>
CakeParticle::CakeParticle(VECTOR pos)
	: position()
	, radius(200.0f)
	, particleCount(0.0f)
	, particlePopTime(2.0f)
	, endFlag(false)
	, xPower(0.0f)
	, yPower(0.0f)
{
	position = pos;

	Initialize();
	Activate();
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
	//パーティクルを飛ばす力をランダム値に
	xPower = -0.5f  + ((float)(rand() % 20) / 20.0f);
	yPower = -0.25f + ((float)(rand() % 20) / 40.0f);
}

/// <summary>
/// 活性化処理
/// </summary>
void CakeParticle::Activate()
{
	particleCount = 0.0f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void CakeParticle::Update(float deltaTime)
{
	radius = ((particlePopTime - particleCount) / particlePopTime) * radius;
	position.x += xPower;
	position.y += yPower;
	position.z = 0.0f;
	
	particleCount += deltaTime;

	if (particleCount > particlePopTime)
	{
		endFlag = true;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void CakeParticle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawSphere3D(position, radius, 8, GetColor(139, 69, 19), GetColor(139, 69, 19), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}