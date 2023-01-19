#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Ball.h"

using namespace std;

/// <summary>
/// �v���C���[�V���b�g�N���X
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet();
	 virtual ~Bullet();

	void Initialize();
	void Activate();
	void Finalize();
	void Update(float deltaTime, Ball* ball);
	void MouseMove(Ball* ball, VECTOR playerPos);		//�}�E�X�J�[�\���̈ړ�
	void SetDead();								//�o���b�g���A�N�e�B�u��
	void SetAlive();							//�o���b�g���A�N�e�B�u��

	bool GetAlive() { return alive; }
	void Draw();
	
private:

	Bullet(const Bullet&);					//�R�s�[�R���X�g���N�^

	void OnShot(float deltaTime);			//���������ꂽ��

	int cursorImage;						//�Ə��摜�i�[�p
	int mouseX;								//�}�E�XX���W
	int mouseZ;								//�}�E�XZ���W
	float worldMouseX;						//���[���h�}�E�XX���W
	float worldMouseZ;						//���[���h�}�E�XZ���W

	bool alive;								//�����Ă邩����ł邩

	//�ÓI�萔
	static const VECTOR SIZE;				//���f���̔{��
	static const VECTOR POSITION;			//���f���̈ʒu
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string CURSOR_PATH;		//�J�[�\���摜�̃p�X
	static const float	SCALE;				//�J�[�\���摜�̑傫��
};