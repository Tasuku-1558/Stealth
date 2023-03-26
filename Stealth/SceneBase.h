#pragma once

//�V�[���̎��
enum class SceneType
{
	TITLE,			//�^�C�g�����
	SELECTION,		//�Z���N�V�������
	GAME,			//�Q�[�����
	RESULT,			//���U���g���
	END,			//�I��
};

/// <summary>
/// �V�[���x�[�X�N���X
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

	int Get() { return number; }
	
protected:

	SceneType nowSceneType;						//���̃V�[��

private:
	SceneBase(const SceneBase&);				//�R�s�[�R���X�g���N�^

	int number;
};