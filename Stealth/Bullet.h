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
	 Bullet();
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition, VECTOR inDir);
	void Update(float deltaTime, Boal* boal);
	void Draw();


private:

	void Move();							//�}�E�X�J�[�\���ړ�
	void OnShot(float deltaTime);			//���������ꂽ��

	int cursorImage;
	VECTOR cursorPosition;
	int mouseX;
	int mouseY;

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const float  SPEED;			//���f���̃X�s�[�h
	static const VECTOR COURSOR_POSITION;
	static const string IMAGE_FOLDER_PATH;		//image�t�H���_�܂ł̃p�X
	static const string CURSOR_PATH;		//�J�[�\���摜�̃p�X


};