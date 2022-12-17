#pragma once

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"
#include <vector>

class Map;

/// <summary>
/// エネミーの状態
/// </summary>
enum class EnemyState
{
	Crawl,			//巡回中
	Arrival,		//目的地に到着
	Discovery,		//プレイヤー発見
};


/// <summary>
/// エネミークラス
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy();		//コンストラクタ
	~Enemy();		//デストラクタ

	void Initialize(Map* map);
	void Activate();
	void Update(float deltaTime);
	void Draw();

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);		//コピーコンストラクタ

	void Position(Map* map);	//エネミー位置設定
	bool IsGoal(float deltaTime);				//目的地に到達したならば
	void eUpdate(float deltaTime);				//状態変化
	void SetTargetPosition();	//移動処理
	void Finalize();

	
	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	VECTOR targetPosition;			//目的地の座標

	const float DELTA = 0.01;

};