#pragma once

#include "ObjectBase.h"
#include "Math3D.h"
#include <string>

using namespace std;

class Boal;

/// <summary>
/// �v���C���[�V���b�g�N���X
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet(Object BOAL);
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Boal* boal);
	void MouseMove(Boal* boal);							//�}�E�X�J�[�\���̈ړ�

	void Draw();

	//�f�o�b�N�p
	int GetMX() { return mouseX; }
	int GetMY() { return mouseY; }

private:

	void OnShot(float deltaTime);			//���������ꂽ��

	int cursorImage;						//�Ə��摜�i�[�p
	int mouseX;								//�}�E�XX���W
	int mouseY;								//�}�E�XY���W

	//�ÓI�萔
	static const VECTOR SIZE;				//���f���̔{��
	static const float  SPEED;				//���f���̃X�s�[�h
	static const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const string CURSOR_PATH;		//�J�[�\���摜�̃p�X

};