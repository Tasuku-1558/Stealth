#pragma once

#include "SceneBase.h"

class FireWorksParticle;

/// <summary>
/// ���U���g�V�[��
/// </summary>
class ResultScene final : public SceneBase
{
public:

	ResultScene(SceneManager* const sceneManager);
	virtual ~ResultScene();

	void Initialize();					//����������
	void Activate();					//����������
	void Update(float deltaTime);		//�X�V����
	void Draw();						//�`�揈��

private:
	ResultScene(const ResultScene&);		//�R�s�[�R���X�g���N�^
	
	void Finalize();					//�I������

	FireWorksParticle* fireWorksParticle;

	int font;				//�Q�[���t�H���g

};