#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// SecondStageMapクラス
/// </summary>
class SecondStageMap final : public StageBase
{
public:
     SecondStageMap();
     virtual ~SecondStageMap();

    void Initialize();      //初期化処理
    void Finalize();        //終了処理
    void Draw();            //描画処理

    std::vector<VECTOR>& GetMap() { return positionList; }          //敵の行動パターンリストを返す
    std::vector<VECTOR>& GetMap2() { return positionList2; }        //敵の行動パターンリスト2を返す

    const int GetModel() { return modelHandle; }                    //マップモデルを返す

private:

    void MapList();                     //敵の行動パターンリスト
    void MapList2();                    //敵の行動パターンリスト2

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;

    std::vector<VECTOR> positionList2;
    std::vector<VECTOR>::iterator itr2;


    //静的定数
    static const VECTOR SIZE;           //モデルの倍率
    static const VECTOR POSITION;       //モデルの位置
};