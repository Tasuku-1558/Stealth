#pragma once

#include "ObjectBase.h"
#include <vector>


/// <summary>
/// セカンドステージマップクラス
/// </summary>
class SecondStageMap final : public ObjectBase
{
public:
     SecondStageMap();
    ~SecondStageMap();

    void Initialize();
    void Finalize();
    void Draw();

    std::vector<VECTOR>& GetMap(int number) { return positionList; }
    std::vector<VECTOR>& GetMap2(int number) { return positionList2; }

    int GetModel() { return modelHandle; }


private:

    void MapList();
    void MapList2();

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;

    std::vector<VECTOR> positionList2;
    std::vector<VECTOR>::iterator itr2;


    //静的定数
    static const VECTOR SIZE;           //モデルの倍率
    static const VECTOR POSITION;       //モデルの位置
};