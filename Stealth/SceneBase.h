#pragma once

#include <vector>
#include <string>
#include "DxLib.h"
#include "PreCompiledHeader.h"


//�V�[���̎��
enum class SceneType
{
	TITLE,		//�^�C�g�����
	SELECTION,	//�Z���N�V�������
	GAME,		//�Q�[�����
	RESULT,		//���U���g���
	END,		//�I��
};

using namespace std;

/// <summary>
/// �V�[�����N���X
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneType sceneType);
	virtual ~SceneBase();

	virtual void Initialize() = 0;					//����������
	virtual SceneType Update(float deltaTime) = 0;	//�X�V����
	virtual void Draw() = 0;						//�`�揈��

	SceneBase* CreateScene(SceneType nowScene);		//�V�����V�[���𐶐�����

protected:
	SceneType nowSceneType;			//���̃V�[��

private:
	SceneBase(const SceneBase&);	//�R�s�[�R���X�g���N�^

};