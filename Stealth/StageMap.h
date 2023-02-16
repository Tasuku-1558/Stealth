#pragma once

#include "StageBase.h"
#include "ModelManager.h"
#include <vector>


/// <summary>
/// ステージマップクラス
/// </summary>
class StageMap final : public StageBase
{
public:
	StageMap(ModelManager::ModelType modelType, VECTOR size, VECTOR rotate, VECTOR position);
	virtual ~StageMap();

	void Initialize();      //初期化処理
	void Draw();            //描画処理

	std::vector<VECTOR>& GetMap(int number) { return positionList[number]; }      //敵の行動パターンリストを返す

private:
	StageMap(const StageMap&);				//コピーコンストラクタ

	void Finalize();						//終了処理

	//FirstStageでの敵の行動
	void MapList();                         //敵の行動パターンリスト(左右移動の敵)

	//SecondStageでの敵の行動
	void MapList2();                        //敵の行動パターンリスト2(壁の周りを回る敵)
	void MapList3();                        //敵の行動パターンリスト3(上下移動の敵)

	//ThirdStageでの敵の行動
	void MapList4();                        //敵の行動パターンリスト4(上下移動の敵)
	void MapList5();                        //敵の行動パターンリスト5(ゴールの位置を塞ぐ敵)

	//FourthStageでの敵の行動
	void MapList6();                        //敵の行動パターンリスト6(左右移動の敵)
	void MapList7();                        //敵の行動パターンリスト7(壁の周りを回る敵)

	//FifthStageでの敵の行動
	void MapList8();                        //敵の行動パターンリスト8(右下L字移動の敵)
	void MapList9();                        //敵の行動パターンリスト9(左上L字移動の敵)

	std::vector<VECTOR> positionList[9];
	std::vector<VECTOR>::iterator itr[9];
};