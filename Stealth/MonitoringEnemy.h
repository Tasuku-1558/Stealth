#pragma once

#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"


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


private:



};