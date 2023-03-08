#pragma once

#include "DxLib.h"
#include "PreCompiledHeader.h"

/// <summary>
/// ObjectBaseクラス
/// </summary>
class ObjectBase
{
public:
	ObjectBase();
	virtual~ObjectBase();
	
	//virtual void Update(float dltaTime) = 0;		//更新処理
	virtual void Draw() = 0;						//描画処理
	
	const VECTOR& GetPosition()  const { return position; }
	const VECTOR& GetDirection() const { return direction; }
	const int& GetModelHandle()  const { return modelHandle; }

protected:

	VECTOR position;	//現在の座標
	VECTOR direction;	//向きベクトル
	int	   modelHandle;	//モデルハンドル
};