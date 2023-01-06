#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Player.h"
#include "Ball.h"


using namespace std;


/// <summary>
/// �v���C���[�V���b�g�N���X
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet(Object BALL);
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Ball* ball);
	void MouseMove(Ball* ball, VECTOR pos);							//�}�E�X�J�[�\���̈ړ�
	void SetDead();							//�o���b�g���A�N�e�B�u��
	void SetAlive();						//�o���b�g���A�N�e�B�u��

	bool GetAlive() { return alive; }
	void Draw();

	//�f�o�b�N�p
	int GetMX() { return mouseX; }
	int GetMY() { return mouseY; }

private:

	void OnShot(float deltaTime);			//���������ꂽ��

	int cursorImage;						//�Ə��摜�i�[�p
	int mouseX;								//�}�E�XX���W
	int mouseY;								//�}�E�XY���W
	float worldMouseX;						//���[���h�}�E�XX���W
	float worldMouseY;						//���[���h�}�E�XY���W

	bool alive;

	//�ÓI�萔
	static const VECTOR SIZE;				//���f���̔{��
	static const float  SPEED;				//���f���̃X�s�[�h
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string CURSOR_PATH;		//�J�[�\���摜�̃p�X

};