//#pragma once
//
//#include "SceneManager.h"
//
//
///// <summary>
///// �X�e�[�W�؂�ւ��N���X
///// </summary>
//class SelectionKey final
//{
//public:
//	SelectionKey(SceneManager* const sceneManager);
//	virtual ~SelectionKey();
//
//	void Initialize();								//����������
//	void Finalize();								//�I������
//	void Activate();								//����������
//	void Draw();									//�`�揈��
//	void KeyMove();									//�L�[���쏈��
//
//private:
//	SelectionKey(const SelectionKey&);				//�R�s�[�R���X�g���N�^
//
//	int StageCreator(int stageNumber);
//	int stageDecrement(int stageNumber);			//�I���X�e�[�W��1�O�Ɏ����Ă���
//	int stageIncrement(int stageNumber);			//�I���X�e�[�W��1��Ɏ����Ă���
//
//
//	int stageMax;									//�ő�X�e�[�W��
//	int stageNo;									//�X�e�[�W�i���o�[
//	bool changeScene;								//�V�[����J�ڂ����邩
//	int changeTimeCount;							//�X�e�[�W�J�ڃJ�E���g
//	int maxTime;									//�}�b�N�X�X�e�[�W�J�ڃJ�E���g
//
//
//};