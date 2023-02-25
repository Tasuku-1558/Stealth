#pragma once

class SceneManager;

/// <summary>
/// SceneBase�N���X
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneManager* const sceneManager) : parent(sceneManager){};
	virtual ~SceneBase(){};

	virtual void Initialize() = 0;				//����������
	virtual void Finalize() = 0;				//�I������
	virtual void Activate() = 0;				//����������
	virtual void Update(float deltaTime) = 0;	//�X�V����
	virtual void Draw() = 0;					//�`�揈��

protected:
	SceneManager* const parent;

	//�V�[���̏��
	//enum Scene
	//{
	//	TITLE,		//�^�C�g�����
	//	SELECTION,	//�I�����
	//	PLAY,		//�Q�[�����
	//	RESULT,		//���U���g���
	//};

private:
	SceneBase(const SceneBase&);				//�R�s�[�R���X�g���N�^
};