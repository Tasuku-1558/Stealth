#pragma once

#include "ObjectBase.h"
#include <vector>


/// <summary>
/// �}�b�v�N���X
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


    //�ÓI�萔
    static const VECTOR SIZE;           //���f���̔{��
    static const VECTOR POSITION;       //���f���̈ʒu
};