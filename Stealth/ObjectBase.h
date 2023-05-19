#pragma once

#include "DxLib.h"
#include "PreCompiledHeader.h"

/// <summary>
/// オブジェクト基底クラス
/// </summary>
class ObjectBase
{
public:
	ObjectBase();
	virtual~ObjectBase();
	
	//virtual void Update(float dltaTime) = 0;		//更新処理
	virtual void Draw() = 0;						//描画処理
	
	const int&	  GetModelHandle() const { return modelHandle; }	//モデルハンドルを返す
	const VECTOR& GetPosition()	   const { return position; }		//座標ベクトルを返す
	const VECTOR& GetDirection()   const { return direction; }		//向きベクトルを返す

protected:

	int	   modelHandle;	//モデルハンドル
	VECTOR position;	//座標ベクトル
	VECTOR direction;	//向きベクトル
};