#pragma once

#include "SceneBase.h"

class Light;
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

	SceneType Update(float deltaTime)override;				//�X�V����
	void Draw()override;									//�`�揈��

	const int GetStage() { return stageNo; }

private:
	StageSelection(const StageSelection&);			//�R�s�[�R���X�g���N�^

	void Initialize()override;						//����������
	void Activate()override;						//����������
	void Finalize()override;						//�I������
	int stageIncrement(int stageNumber);			//�I���X�e�[�W��1��Ɏ����Ă���
	int stageDecrement(int stageNumber);			//�I���X�e�[�W��1�O�Ɏ����Ă���
	void StageCreator(int stageNumber);				//�e�V�[���֑J��
	void KeyMove(float deltaTime);					//�L�[����

	Light* light;
	Camera* camera;
	SelectionUi* selectionUi;
	FadeManager* fadeManager;

	int font;										//�Q�[���t�H���g
	int stageMax;									//�ő�X�e�[�W��
	int stageNo;									//�X�e�[�W�i���o�[
	int changeTimeCount;							//�X�e�[�W�J�ڃJ�E���g
	float frame;									//�t���[����
	float pushCount;								//�X�e�[�W�؂�ւ��J�E���g
	bool changeScene;								//�V�[����J�ڂ����邩

	//�萔
	const int	STAGE_NUMBER;						//�X�e�[�W�̐�
	const int   MAX_TIME;							//�}�b�N�X�X�e�[�W�J�ڃJ�E���g
	const int   FIRST_STAGE_NUMBER;					//�ŏ��ɕ\�������X�e�[�W
	const float PUSH_INTERVAL;						//�؂�ւ��J�E���g�̃C���^�[�o��

};