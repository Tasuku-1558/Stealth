#pragma once

#include "ObjectBase.h"
#include <vector>


/// <summary>
/// マップクラス
/// </summary>
class Stage2Map final : public ObjectBase
{
public:
     Stage2Map();
    ~Stage2Map();

    void Initialize();
    void Finalize();
    void Draw();

    std::vector<VECTOR>& GetMap(int number) { return positionList; }

    int GetModel() { return modelHandle; }


private:

    void MapList();

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;


    //静的定数
    static const VECTOR SIZE;           //モデルの倍率
    static const VECTOR POSITION;       //モデルの位置
};