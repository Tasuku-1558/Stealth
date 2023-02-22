#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Cake.h"

using namespace std;

/// <summary>
/// �P�[�L���˃N���X
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet();
	 virtual ~Bullet();

	void Initialize();									//����������
	void Activate();									//����������
	void Finalize();									//�I������
	void Update(float deltaTime);						//�X�V����
	void Draw();										//�`�揈��
	void MouseMove(Cake* cake, VECTOR playerPos);		//�}�E�X�J�[�\���̈ړ�
	void BulletDead();									//�o���b�g���A�N�e�B�u��
	void BulletAlive();									//�o���b�g���A�N�e�B�u��

	const bool GetAlive() { return alive; }				//�o���b�g�������Ă邩����ł邩��Ԃ�
	
private:
	Bullet(const Bullet&);					//�R�s�[�R���X�g���N�^

	void OnShot();							//���������ꂽ��

	int cursorImage;						//�Ə��摜�i�[�p
	int mouseX;								//�}�E�XX���W
	int mouseZ;								//�}�E�XZ���W
	float worldMouseX;						//���[���h�}�E�XX���W
	float worldMouseY;						//���[���h�}�E�XY���W
	float worldMouseZ;						//���[���h�}�E�XZ���W
	bool alive;								//�o���b�g�������Ă邩����ł邩


	//�萔
	const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	const string CURSOR_PATH;		//�J�[�\���摜�̃p�X
	const VECTOR SIZE;				//���f���̔{��
	const VECTOR POSITION;			//���f���̈ʒu
	const float	 SCALE;				//�J�[�\���摜�̑傫��
};