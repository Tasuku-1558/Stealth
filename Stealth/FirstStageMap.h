#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// �X�e�[�W1�}�b�v�N���X
/// </summary>
class FirstStageMap final : public StageBase
{
public:
     FirstStageMap();
     virtual ~FirstStageMap();

    void Initialize();      //����������
    void Finalize();        //�I������
    void Draw();            //�`�揈��

    std::vector<VECTOR>& GetMap() { return positionList; }      //�G�̍s���p�^�[�����X�g��Ԃ�

private:

    void MapList();                    //�G�̍s���p�^�[�����X�g(���E�ړ��̓G)

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;
    

    //�ÓI�萔
    static const VECTOR SIZE;           //���f���̔{��
    static const VECTOR POSITION;       //���f���̈ʒu
    static const VECTOR ROTATE;         //���f���̉�]�l

};