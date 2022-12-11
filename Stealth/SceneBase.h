#pragma once


class SceneBase
{
public:
	SceneBase() {/*�����Ȃ�*/ }			//�R���X�g���N�^
	virtual ~SceneBase() {/*�����Ȃ�*/}	//�f�X�g���N�^

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:


private:
	SceneBase(const SceneBase&);		//�R�s�[�R���X�g���N�^
};