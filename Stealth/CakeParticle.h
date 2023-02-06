#pragma once

#include "DxLib.h"

/// <summary>
/// ケーキパーティクルクラス
/// マウスクリック時に出すパーティクル
/// </summary>
class CakeParticle final
{
public:
	CakeParticle(VECTOR pos);
	virtual ~CakeParticle();

	void Initialize();				//初期化処理
	void Activate();				//活性化処理
	void Update(float deltaTime);	//更新処理
	void Draw();					//描画処理

	const bool IsParticleEnd() { return endFlag; }		//パーティクルを消すフラグを返す

private:
	CakeParticle(const CakeParticle&);	//コピーコンストラクタ

	VECTOR position;		//パーティクルの位置
	float radius;			//パーティクルの半径
	float particleCount;	//パーティクルカウント
	float particlePopTime;	//パーティクルの出現時間
	bool endFlag;			//パーティクルを消す
	float xPower;			//横方向の力
	float zPower;			//縦方向の力


	//静的定数
	//パーティクルのカラー
	static const unsigned int Color;
};