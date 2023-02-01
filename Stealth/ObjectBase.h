#pragma once

#include "DxLib.h"


/// <summary>
/// ObjectBaseクラス
/// </summary>
class ObjectBase
{
public:
	  ObjectBase();
	  virtual~ObjectBase();

	  virtual void Initialize() = 0;					//初期化処理
	  //virtual void Update(float dltaTime) = 0;		//更新処理
	  //virtual void Draw() = 0;						//描画処理

	  const VECTOR& GetPosition() const; 	//positionのgetter
	  const VECTOR& GetDir() const;			//dirのgetter
	  const int& GetModelHandle() const; 	//modelHandleのgetter

	  //オブジェクトのタグ
	  enum class Object
	  {
		  PLAYER,		//プレイヤー
		  CAKE,			//ケーキ
		  WALL,			//壁
	  };

protected:
	VECTOR position;	//現在の座標
	VECTOR dir;			//向きベクトル
	int modelHandle;	//モデルハンドル
	Object object;		//オブジェクトのタグ
};