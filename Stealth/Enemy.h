#pragma once

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Field;

//エネミーの状態
enum class EnemyState
{
	Nomal,
	Attack,
};

//エネミークラス
class Enemy final : public EnemyBase
{
public:
	 Enemy();		//コンストラクタ
	~Enemy();		//デストラクタ

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime,Field* field);
	void Draw();

	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);		//コピーコンストラクタ

	void eUpdate();						//状態変化
	void GoBuck(float deltaTime,Field* field);		//エネミー各行動パターン

	
};