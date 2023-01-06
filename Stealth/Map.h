#pragma once

#include "ObjectBase.h"
#include "Math3D.h"
#include <vector>

/// <summary>
/// マップクラス
/// </summary>
class Map final : public ObjectBase
{
public:
     Map();
    ~Map();

    void Initialize();
    void Finalize();
    void Activate();
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