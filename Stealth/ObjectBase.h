#pragma once

#include "DxLib.h"


class ObjectBase
{
public:
			  ObjectBase();		//コンストラクタ
	  virtual~ObjectBase();		//デストラクタ

	  virtual void Initialize() = 0;
	  virtual void Activate() = 0;
	  //virtual void Update(float dltaTime) = 0;				
	  virtual void Draw() = 0;

	  const VECTOR& GetPosition() const; 	//positionのgetter
	  const VECTOR& GetDir() const;			//dirのgetter

protected:
	VECTOR position;						//現在の座標
	VECTOR dir;								//向きベクトル
	int	   modelHandle;						//モデルハンドル

};