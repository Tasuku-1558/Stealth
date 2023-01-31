#pragma once

#include "SceneBase.h"
#include "SceneManager.h"


class Light;
class SelectionUi;
class FadeManager;


/// <summary>
/// �X�e�[�W�I����ʃN���X
/// </summary>
class StageSelection final : public SceneBase
{
public:
	 StageSelection(SceneManager* const sceneManager);
	 virtual ~StageSelection();

	void Initialize();								//����������
	void Finalize();								//�I������
	void Activate();								//����������
	void Update(float deltaTime);					//�X�V����
	void Draw();									//�`�揈��


private:
	StageSelection(const StageSelection&);			//�R�s�[�R���X�g���N�^


	Light* light;
	SelectionUi* selectionUi;
	FadeManager* fadeManager;

	int StageCreator(int stageNumber);
	int stageDecrement(int stageNumber);			//�I���X�e�[�W��1�O�Ɏ����Ă���
	int stageIncrement(int stageNumber);			//�I���X�e�[�W��1��Ɏ����Ă���
	void KeyMove(float deltaTime);					//�L�[����

	
	int font;										//�Q�[���t�H���g
	int stageMax;									//�ő�X�e�[�W��
	int stageNo;									//�X�e�[�W�i���o�[
	bool changeScene;								//�V�[����J�ڂ����邩
	int changeTimeCount;							//�X�e�[�W�J�ڃJ�E���g
	int maxTime;									//�}�b�N�X�X�e�[�W�J�ڃJ�E���g
	float pushCount;								//�X�e�[�W�؂�ւ��J�E���g

	int frame;
	//�ÓI�萔
	static const float PUSH_INTERVAL;				//�؂�ւ��J�E���g�̃C���^�[�o��

};