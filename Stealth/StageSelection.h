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

	enum class State
	{
		STAGE1,
		STAGE2,
		TITLE,
	};

private:
	StageSelection(const StageSelection&);		//�R�s�[�R���X�g���N�^

	int StageCreator(int stageNum);
	int stageDecrement(int stageNum);     // �I���X�e�[�W��1�O��
	int stageIncrement(int stageNum);     // �I���X�e�[�W��1���


	FadeManager* fadeManager;


	State state;
	int selectionHandle;						//�I���摜�n���h��
	int stageNumMax;
	int stageNo;
	int i;
	int frame;

	
	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string SELECTION_PATH;		//�I���摜�̃p�X
};