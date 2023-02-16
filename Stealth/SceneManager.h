#pragma once

class SceneBase;

/// <summary>
/// �V�[���}�l�[�W���[�N���X
/// </summary>
class SceneManager final
{
public:

	 SceneManager();
	 virtual ~SceneManager();

	void Initialize();				//����������
	void Finalize();				//�I������
	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

	//�V�[���̏��
	enum Scene
	{
		TITLE,			//�^�C�g�����
		SELECTION,		//�X�e�[�W�I�����
		STAGE1,			//�X�e�[�W1���
		STAGE2,			//�X�e�[�W2���
		STAGE3,			//�X�e�[�W3���
		STAGE4,			//�X�e�[�W4���
		STAGE5,			//�X�e�[�W5���
		RESULT,			//���U���g���
		END				//�I���ƃV�[����
	};

	void  SetNextScene(Scene next);		//���̃V�[�����Z�b�g
	Scene GetNowScene();				//���̃V�[�����擾
	Scene GetNextScene();				//���̃V�[�����擾

private:

	SceneManager(const SceneManager&);	//�R�s�[�R���X�g���N�^

	SceneBase* eachScene[Scene::END];	//�e�V�[���̃C���X�^���X
	SceneBase* nowPointer;				//���̃V�[���|�C���^
	Scene	   nowScene;				//���̃V�[��
	Scene	   nextScene;				//���̃V�[��

	void ChangeScene();					//�V�[���̕ύX
};