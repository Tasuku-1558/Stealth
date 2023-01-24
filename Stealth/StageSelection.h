#pragma once

#include "SceneBase.h"
#include "SceneManager.h"
#include <string>

class FadeManager;

using namespace std;

/// <summary>
/// �X�e�[�W�I����ʃN���X
/// </summary>
class StageSelection final : public SceneBase
{
public:
	 StageSelection(SceneManager* const sceneManager);
	~StageSelection();

	void Initialize();								//����������
	void Finalize();								//�I������
	void Activate();								//����������
	void Update(float deltaTime);					//�X�V����
	void Draw();									//�`�揈��


private:
	StageSelection(const StageSelection&);			//�R�s�[�R���X�g���N�^

	int StageCreator(int stageNumber);
	int stageDecrement(int stageNumber);			//�I���X�e�[�W��1�O�Ɏ����Ă���
	int stageIncrement(int stageNumber);			//�I���X�e�[�W��1��Ɏ����Ă���


	FadeManager* fadeManager;

	int font;										//�Q�[���t�H���g
	int arrowKeyImage;								//���L�[�摜
	int enterKeyImage;								//�G���^�[�L�[�摜
	int stageMapHandle[2];							//�X�e�[�W�}�b�v�̉摜�n���h��
	int stageDescription[2];						//�X�e�[�W�̐����摜�n���h��
	int stageMax;									//�ő�X�e�[�W��
	int stageNo;									//�X�e�[�W�i���o�[
	bool changeScene;								//�V�[����J�ڂ����邩
	int changeTimeCount;							//�X�e�[�W�J�ڃJ�E���g
	int maxTime;									//�}�b�N�X�X�e�[�W�J�ڃJ�E���g


	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;			//image�t�H���_�܂ł̃p�X
	static const string ARROW_KEY_PATH;				//���L�[�摜�̃p�X
	static const string ENTER_KEY_PATH;				//�G���^�[�L�[�摜�̃p�X
	static const string STAGE1_MAP_PATH;			//�X�e�[�W1�}�b�v�̉摜�̃p�X
	static const string STAGE2_MAP_PATH;			//�X�e�[�W2�}�b�v�̉摜�̃p�X
	static const string STAGE1_DESCRIPTION_PAHT;	//�X�e�[�W1�̐����摜�̃p�X
	static const string STAGE2_DESCRIPTION_PAHT;	//�X�e�[�W2�̐����摜�̃p�X
	static const int	STAGE_IMAGE_NUMBER;			//�X�e�[�W�摜��
};