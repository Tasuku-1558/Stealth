#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// セカンドステージマップクラス
/// </summary>
class SecondStageMap final : public StageBase
{
public:
     SecondStageMap();
     virtual ~SecondStageMap();

    void Initialize();
    void Finalize();
    void Draw();

    std::vector<VECTOR>& GetMap() { return positionList; }
    std::vector<VECTOR>& GetMap2() { return positionList2; }

    int GetModel() { return modelHandle; }

private:

    void MapList();
    void MapList2();

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;

    std::vector<VECTOR> positionList2;
    std::vector<VECTOR>::iterator itr2;
    int count;

    //静的定数
    static const VECTOR SIZE;           //モデルの倍率
    static const VECTOR POSITION;       //モデルの位置
};