#pragma once

#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;


/// <summary>
/// 監視エネミークラス
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(std::vector<VECTOR>& id);
	virtual ~MonitoringEnemy();

	void Initialize();									//初期化処理
	void Activate();									//活性化処理
	void Update(float deltaTime);						//更新処理
	void Draw();										//描画処理

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//エネミーの視野にケーキが入った場合
	void VisualAngleWall(VECTOR wallPos);					//エネミーの視野に壁が入った場合


	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す
	const int GetPlayerCount() { return playerFindCount; }	//プレイヤーを見つけた回数を返す

	//エネミーの状態
	enum class EnemyState
	{
		CRAWL,			//巡回中
		ARRIVAL,		//目的地に到着
	};

private:
	MonitoringEnemy(const MonitoringEnemy&);				//コピーコンストラクタ


	EnemyState enemyState;						//エネミーの状態


};