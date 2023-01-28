#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// FirstStageMapクラス
/// </summary>
class Map final : public StageBase
{
public:
     Map();
     virtual ~Map();

    void Initialize();      //初期化処理
    void Finalize();        //終了処理
    void Draw();            //描画処理

    std::vector<VECTOR>& GetMap() { return positionList; }      //敵の行動パターンリストを返す
    const int GetModel() { return modelHandle; }                //マップモデルを返す

private:

    void MapList();                    //敵の行動パターンリスト

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;
    

    //静的定数
    static const VECTOR SIZE;           //モデルの倍率
    static const VECTOR POSITION;       //モデルの位置
    static const VECTOR ROTATE;         //モデルの回転値

};