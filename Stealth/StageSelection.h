#pragma once

#include "SceneBase.h"
#include <string>

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

	int selectionHandle;						//�I���摜�n���h��

	//�ÓI�萔
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string SELECTION_PATH;		//�I���摜�̃p�X
};