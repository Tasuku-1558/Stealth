#pragma once

class SceneManager;

/// <summary>
/// �V�[���x�[�X�N���X
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneManager* const sceneManager) : parent(sceneManager) {/*�����Ȃ�*/ }	//�R���X�g���N�^
	virtual ~SceneBase() {/*�����Ȃ�*/}	//�f�X�g���N�^

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	SceneManager* const parent;

private:
	SceneBase(const SceneBase&);		//�R�s�[�R���X�g���N�^
};