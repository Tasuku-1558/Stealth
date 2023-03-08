#pragma once

//class SceneManager;

enum class SceneType
{
	TITLE,
	SELECTION,
	PLAY,
	RESULT,
	END
};

/// <summary>
/// SceneBase�N���X
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneType sceneType) : nowSceneType(sceneType) { /*�����Ȃ�*/ }
	virtual ~SceneBase(){/*�����Ȃ�*/}

	virtual void Initialize() = 0;				//����������
	virtual void Finalize() = 0;				//�I������
	virtual void Activate() = 0;				//����������
	virtual SceneType Update(float deltaTime) = 0;	//�X�V����
	virtual void Draw() = 0;					//�`�揈��

	
protected:

	SceneType nowSceneType; //����SceneType


private:
	SceneBase(const SceneBase&);				//�R�s�[�R���X�g���N�^
};