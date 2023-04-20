#pragma once

#include "ObjectBase.h"
#include "ModelManager.h"


/// <summary>
/// ステージクラス
/// </summary>
class Stage final : public ObjectBase
{
public:
	Stage(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position);
	virtual ~Stage();

	void Draw();    //描画処理

private:
	Stage(const Stage&);	//コピーコンストラクタ

	void Finalize();	//終了処理

	int stageModel;
};