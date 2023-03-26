#pragma once

#include "ObjectBase.h"
#include "ModelManager.h"


/// <summary>
/// ステージマップクラス
/// </summary>
class StageMap final : public ObjectBase
{
public:
	StageMap(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position);
	virtual ~StageMap();

	void Initialize();      //初期化処理
	void Draw();            //描画処理

private:
	StageMap(const StageMap&);				//コピーコンストラクタ

	void Finalize();						//終了処理

	int kabe;
	int frameNo;

};