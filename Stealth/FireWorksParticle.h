#pragma once

#include "DxLib.h"

/// <summary>
/// 花火パーティクルクラス
/// リザルト画面で出すパーティクル
/// </summary>
class FireWorksParticle final
{
public:
	FireWorksParticle(const VECTOR& pos);
	virtual ~FireWorksParticle();

	void Initialize();				//初期化処理
	void Activate();				//活性化処理
	void Update(float deltaTime);	//更新処理
	void Draw();					//描画処理

	const bool IsParticleEnd() { return endFlag; }		//パーティクルを消すフラグを返す

private:
	FireWorksParticle(const FireWorksParticle&);	//コピーコンストラクタ

	VECTOR position;		//パーティクルの位置
	float radius;			//パーティクルの半径
	float particleCount;	//パーティクルカウント
	float particlePopTime;	//パーティクルの出現時間
	bool endFlag;			//パーティクルを消す
	float xPower;			//横方向の力
	float yPower;			//縦方向の力


	//静的定数
	static const unsigned int ORANGE;		//パーティクルのカラー
};