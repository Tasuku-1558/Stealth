#pragma once

#include "DxLib.h"
#include "PlayerBase.h"
#include "Math3D.h"
#include "Collision.h"
#include "EffectManager.h"
#include "HitChecker.h"


/// <summary>
/// プレイヤークラス
/// </summary>
class Player final : public PlayerBase
{
public:
	Player(EffectManager* const inEffect, HitChecker* const inHitChecker);
	virtual ~Player();

	void Update(float deltaTime);									//更新処理
	void Draw();													//描画処理
	void FoundEnemy(float deltaTime, bool spotted);					//エネミーに見つかった場合

	const int FindCount() { return playerFindCount; }				//エネミーに見つかった回数を返す
	const My3dLib::Sphere GetCollide() { return collisionSphere; }	//当たり判定球を返す

private:
	Player(const Player&);			//コピーコンストラクタ

	void Initialize();				//初期化処理
	void Move(float deltaTime);		//移動処理
	void Finalize();				//終了処理
	void KeyInput();				//キー入力処理
	void AfterImage();				//プレイヤーの残像処理
	void FoundCount();				//エネミーに見つかった時の初期位置へ戻すカウント
	void HitMap();					//マップに衝突した

	//キー入力
	struct Key
	{
		int input;	//キー操作
		VECTOR dir;	//方向
	};

	EffectManager* effectManager;	//エフェクトマネージャーのポインタ
	HitChecker* hitChecker;			//ヒットチェッカーのポインタ

	My3dLib::Sphere collisionSphere;	//当たり判定球
};