#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// SecondStageMap�N���X
/// </summary>
class SecondStageMap final : public StageBase
{
public:
     SecondStageMap();
     virtual ~SecondStageMap();

    void Initialize();      //����������
    void Finalize();        //�I������
    void Draw();            //�`�揈��

    std::vector<VECTOR>& GetMap() { return positionList; }          //�G�̍s���p�^�[�����X�g��Ԃ�
    std::vector<VECTOR>& GetMap2() { return positionList2; }        //�G�̍s���p�^�[�����X�g2��Ԃ�

    const int GetModel() { return modelHandle; }                    //�}�b�v���f����Ԃ�

private:

    void MapList();                     //�G�̍s���p�^�[�����X�g
    void MapList2();                    //�G�̍s���p�^�[�����X�g2

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;

    std::vector<VECTOR> positionList2;
    std::vector<VECTOR>::iterator itr2;


    //�ÓI�萔
    static const VECTOR SIZE;           //���f���̔{��
    static const VECTOR POSITION;       //���f���̈ʒu
};