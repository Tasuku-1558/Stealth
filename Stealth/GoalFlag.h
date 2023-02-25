#pragma once

#include "ObjectBase.h"
#include "Math3D.h"


/// <summary>
/// ゴールフラッグクラス
/// </summary>
class GoalFlag final : public ObjectBase
{
public:
	GoalFlag(VECTOR pos);
	virtual ~GoalFlag();

	void Initialize();					//初期化処理
	void Finalize();					//終了処理
	void Update(float deltaTime);		//更新処理
	void Draw();						//描画処理

private:
	GoalFlag(const GoalFlag&);			//コピーコンストラクタ

	VECTOR rotate;						//モデルの回転


	//定数
	const VECTOR SIZE;           //モデルの倍率
	const VECTOR ROTATE_SPEED;	 //モデルの回転スピード

};