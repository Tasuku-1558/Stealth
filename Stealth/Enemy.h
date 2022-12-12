#pragma once

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"


/// <summary>
/// エネミーの状態
/// </summary>
enum class EnemyState
{
	Crawl,			//巡回モード
	Tracking,		//追尾モード
};

/// <summary>
/// エネミークラス
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy();		//コンストラクタ
	~Enemy();		//デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);		//コピーコンストラクタ

	void eUpdate();						//状態変化
	void GoBuck(float deltaTime);		//エネミー各行動パターン

	
};