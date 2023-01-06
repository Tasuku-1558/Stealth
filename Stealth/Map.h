#pragma once

#include "ObjectBase.h"
#include "Math3D.h"
#include <vector>

/// <summary>
/// �}�b�v�N���X
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


    //�ÓI�萔
    static const VECTOR SIZE;           //���f���̔{��
    static const VECTOR POSITION;       //���f���̈ʒu

};