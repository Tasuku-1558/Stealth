#pragma once

#include "StageBase.h"
#include <vector>


/// <summary>
/// �X�e�[�W3�}�b�v�N���X
/// </summary>
class ThirdStageMap final : public StageBase
{
public:
	ThirdStageMap();
	virtual ~ThirdStageMap();

    void Initialize();      //����������
    void Draw();            //�`�揈��

    std::vector<VECTOR>& GetMap()  { return positionList; }         //�G�̍s���p�^�[�����X�g��Ԃ�
    std::vector<VECTOR>& GetMap2() { return positionList2; }        //�G�̍s���p�^�[�����X�g2��Ԃ�

private:
    ThirdStageMap(const ThirdStageMap&);    //�R�s�[�R���X�g���N�^

    void MapList();                     //�G�̍s���p�^�[�����X�g(�㉺�Ɉړ�����G)
    void MapList2();                    //�G�̍s���p�^�[�����X�g2(�S�[���̈ʒu���ǂ��G)


    void Finalize();                    //�I������

    std::vector<VECTOR> positionList;
    std::vector<VECTOR>::iterator itr;

    std::vector<VECTOR> positionList2;
    std::vector<VECTOR>::iterator itr2;

    //�ÓI�萔
    static const VECTOR SIZE;           //���f���̔{��
    static const VECTOR POSITION;       //���f���̈ʒu
    static const VECTOR ROTATE;         //���f���̉�]�l


};