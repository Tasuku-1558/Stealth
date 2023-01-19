#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// �t�@�[�X�g�X�e�[�W�}�b�v�N���X
/// </summary>
class Map final : public StageBase
{
public:
     Map();             //�R���X�g���N�^
     virtual ~Map();    //�f�X�g���N�^

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
    

    //�ÓI�萔
    static const VECTOR SIZE;           //���f���̔{��
    static const VECTOR POSITION;       //���f���̈ʒu
    static const VECTOR ROTATE;         //���f���̉�]�l

};