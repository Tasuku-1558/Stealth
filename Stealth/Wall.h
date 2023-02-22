#pragma once

#include "ObjectBase.h"

/// <summary>
/// 壁クラス
/// </summary>
class Wall final : public ObjectBase
{
public:

	 Wall(VECTOR pos);
	 virtual ~Wall();

	void Initialize();					//初期化処理
	void Finalize();					//終了処理
	void Draw();						//描画処理

private:

	Wall(const Wall&);					//コピーコンストラクタ

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const VECTOR POSITION;		//モデルの位置

};