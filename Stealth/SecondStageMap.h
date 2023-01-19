#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// �Z�J���h�X�e�[�W�}�b�v�N���X
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

    //�ÓI�萔
    static const VECTOR SIZE;           //���f���̔{��
    static const VECTOR POSITION;       //���f���̈ʒu
};