#pragma once

class SceneBase;

/// <summary>
/// �V�[���}�l�[�W���[�N���X
/// </summary>
class SceneManager final
{
public:

	/// <summary>
	/// �V�[���̏��
	/// </summary>
	enum Scene
	{
		TITLE,			//�^�C�g�����
		SELECTION,		//�X�e�[�W�I�����
		STAGE1,			//�X�e�[�W1���
		STAGE2,			//�X�e�[�W2���
		//OVER,			//�Q�[���I�[�o�[���
		END				//�I���ƃV�[����
	};

	 SceneManager();
	~SceneManager();

	void Initialize();
	void Finalize();
	void Update(float deltaTime);
	void Draw();

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