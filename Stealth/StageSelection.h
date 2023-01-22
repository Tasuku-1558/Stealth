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

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();


private:
	StageSelection(const StageSelection&);		//�R�s�[�R���X�g���N�^

	int StageCreator(int stageNum);
	int stageDecrement(int stageNum);     //�I���X�e�[�W��1�O��
	int stageIncrement(int stageNum);     //�I���X�e�[�W��1���


	FadeManager* fadeManager;

	int font;					//�Q�[���t�H���g
	int selectionHandle;		//�X�e�[�W�I���摜�n���h��
	int stage1MapHandle;		//�X�e�[�W1�}�b�v�̉摜�n���h��
	int stage1Description;		//�X�e�[�W1�̐����摜�n���h��
	int stage2MapHandle;		//�X�e�[�W2�}�b�v�̉摜�n���h��
	int stage2Description;		//�X�e�[�W2�̐����摜�n���h��
	int stageMax;				//�ő�X�e�[�W��
	int stageNo;				//�X�e�[�W�i���o�[
	bool changeScene;			//�V�[����J�ڂ����邩
	int changeTimeCount;		//�X�e�[�W�J�ڃJ�E���g
	int maxTime;				//�}�b�N�X�X�e�[�W�J�ڃJ�E���g


	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;			//image�t�H���_�܂ł̃p�X
	static const string SELECTION_PATH;				//�I���摜�̃p�X
	static const string STAGE1_MAP_PATH;			//�X�e�[�W1�}�b�v�̉摜�̃p�X
	static const string STAGE1_DESCRIPTION_PAHT;	//�X�e�[�W1�̐����摜�̃p�X
	static const string STAGE2_MAP_PATH;			//�X�e�[�W2�}�b�v�̉摜�̃p�X
	static const string STAGE2_DESCRIPTION_PAHT;	//�X�e�[�W2�̐����摜�̃p�X

};