#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"
#include "Cake.h"

class Player;

using namespace std;

/// <summary>
/// �P�[�L���˃N���X
/// </summary>
class Bullet final : public ObjectBase
{
public:
	Bullet();
	virtual ~Bullet();

	void Update(float deltaTime);						//�X�V����
	void Draw();										//�`�揈��

	void MouseMove(Cake* cake, Player* player);			//�}�E�X�J�[�\���̈ړ�
	void BulletDead();									//�o���b�g���A�N�e�B�u��
	void BulletAlive();									//�o���b�g���A�N�e�B�u��

	const bool GetAlive() { return alive; }				//�o���b�g�������Ă邩����ł邩��Ԃ�
	
private:
	Bullet(const Bullet&);					//�R�s�[�R���X�g���N�^

	void Initialize();						//����������
	void Activate();						//����������
	void Finalize();						//�I������
	void OnShot();							//���������ꂽ��

	int cursorImage;						//�Ə��摜�i�[�p
	int mouseX;								//�}�E�XX���W
	int mouseY;								//�}�E�XY���W
	float worldMouseX;						//���[���h�}�E�XX���W
	float worldMouseY;						//���[���h�}�E�XY���W
	float worldMouseZ;						//���[���h�}�E�XZ���W
	bool alive;								//�o���b�g�������Ă邩����ł邩

	My3dLib::Sphere collisionSphere;		//�����蔻�苅

	//�萔
	const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	const string CURSOR_PATH;		//�J�[�\���摜�̃p�X
	const VECTOR SIZE;				//���f���̔{��
	const VECTOR POSITION;			//���f���̈ʒu
	const VECTOR ROTATE;			//���f���̉�]�l
	const float	 SCALE;				//�J�[�\���摜�̑傫��
	const float  RADIUS;			//�P�[�L�̔��a
};