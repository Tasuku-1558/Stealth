#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// ファーストステージマップクラス
/// </summary>
class Map final : public StageBase
{
public:
     Map();             //コンストラクタ
     virtual ~Map();    //デストラクタ

    void Initialize();
    void Finalize();
    void Draw();

    std::vector<VECTOR>& GetMap() { return positionList; }
    int GetModel() { return modelHandle; }

private:

    void MapList();
    void MiniMap();

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;
    

    //静的定数
    static const VECTOR SIZE;           //モデルの倍率
    static const VECTOR POSITION;       //モデルの位置
    static const VECTOR ROTATE;         //モデルの回転値

};