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
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);		//コピーコンストラクタ

	void Position(Map* map);
	void eUpdate();								//状態変化
	void ActionPattern(float deltaTime);		//エネミー各行動パターン

	
	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;
	
};