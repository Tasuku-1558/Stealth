#pragma once

#include "SceneBase.h"

class Camera;
class SelectionUi;
class FadeManager;


/// <summary>
/// �X�e�[�W�I����ʃN���X
/// </summary>
class StageSelection final : public SceneBase
{
public:
	StageSelection();
	virtual ~StageSelection();

	SceneType Update(float deltaTime)override;		//�X�V����
	void Draw()override;							//�`�揈��

private:
	StageSelection(const StageSelection&);			//�R�s�[�R���X�g���N�^

	void Initialize()override;						//����������
	void KeyMove(float deltaTime);					//�L�[����
	int stageIncrement(int stageNumber);			//�I���X�e�[�W��1��Ɏ����Ă���
	int stageDecrement(int stageNumber);			//�I���X�e�[�W��1�O�Ɏ����Ă���
	int StageCreator(int stageNumber);				//�e�V�[���֑J��

	Camera* camera;
	SelectionUi* selectionUi;
	FadeManager* fadeManager;

	struct Stage
	{
		int number;				//�X�e�[�W�ԍ�
		SceneType sceneType;	//�V�[���̎��
	};

	struct StageUi
	{
		int number;			//�X�e�[�W�ԍ�
		int mapNumber;		//�}�b�v�̔ԍ�
		int enemyNumber;	//�G�̐�
		int cakeNumber;		//�P�[�L�̐�
	};

	int fontHandle;							//�Q�[���t�H���g
	int stageNo;							//�X�e�[�W�ԍ�
	int changeTimeCount;					//�����_�ŃJ�E���g
	float fadeCount;						//�t�F�[�h�J�E���g
	float pushCount;						//�X�e�[�W�؂�ւ��J�E���g
	bool changeScene;						//�V�[����؂�ւ���
	

	//�萔
	const int   MAX_STAGE;					//�ő�X�e�[�W��
	const int	FIRST_STAGE_NUMBER;			//�X�e�[�W1�̔ԍ�
	const int	SECOND_STAGE_NUMBER;		//�X�e�[�W2�̔ԍ�
	const int	THIRD_STAGE_NUMBER;			//�X�e�[�W3�̔ԍ�
	const int	FOURTH_STAGE_NUMBER;		//�X�e�[�W4�̔ԍ�
	const int	FIFTH_STAGE_NUMBER;			//�X�e�[�W5�̔ԍ�
	const int	TITLE_RETURN_NUMBER;		//�^�C�g���֖߂�ԍ�
	const int   ADD_STAGE_NUMBER;			//�X�e�[�W��؂�ւ��鐔
	const int	SELECTION_FONT_SIZE;		//�Q�[���t�H���g�̃T�C�Y
	const int	FONT_THICK;					//�t�H���g�̑���
	const float MAX_PUSH_COUNT;				//�ő�؂�ւ��J�E���g
	const float PUSH_INTERVAL;				//�؂�ւ��J�E���g�̃C���^�[�o��
	const float FADE_START_COUNT;			//�t�F�[�h�J�n�J�E���g

};