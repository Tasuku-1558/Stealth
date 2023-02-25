#pragma once

#include "DxLib.h"

/// <summary>
/// パーティクルベースクラス
/// </summary>
class ParticleBase
{
public:

	ParticleBase();
	virtual ~ParticleBase();

	virtual void Initialize() = 0;				//初期化処理
	virtual void Activate() = 0;				//活性化処理
	virtual void Update(float deltaTime) = 0;	//更新処理
	virtual void Draw() = 0;					//描画処理

	const bool IsParticleEnd() { return endFlag; }		//パーティクルを消すフラグを返す

protected:

	VECTOR position;		//パーティクルの位置
	float radius;			//パーティクルの半径
	float particleCount;	//パーティクルカウント
	float particlePopTime;	//パーティクルの出現時間
	bool endFlag;			//パーティクルを消すか消さないか
	float xPower;			//横方向の力
	float zPower;			//縦方向の力
};