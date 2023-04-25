#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"
#include "Cake.h"
#include "Player.h"

using namespace std;

/// <summary>
/// �P�[�L���˃N���X
/// </summary>
class Bullet final : public ObjectBase
{
public:
	Bullet(Player* const inPlayer);
	virtual ~Bullet();

	void Update(float deltaTime);				//�X�V����
	void Draw();								//�`�揈��

	void MouseMove(Cake* cake);					//�}�E�X�J�[�\���̈ړ�
	void BulletDead();							//�o���b�g���A�N�e�B�u��
	void BulletAlive();							//�o���b�g���A�N�e�B�u��

	const bool GetAlive() { return alive; }		//�o���b�g�������Ă邩����ł邩��Ԃ�
	
private:
	Bullet(const Bullet&);				//�R�s�[�R���X�g���N�^

	void Initialize();					//����������
	void Finalize();					//�I������
	void OnShot();						//���������ꂽ��

	int cursorImage;					//�Ə��摜�i�[�p
	int mouseX;							//�}�E�XX���W
	int mouseY;							//�}�E�XY���W
	bool alive;							//�o���b�g�������Ă邩����ł邩
	VECTOR worldMouse;					//���[���h�}�E�X���W

	My3dLib::Sphere collisionSphere;	//�����蔻�苅

	Player* player;						//�v���C���[�̃|�C���^

	//�萔
	const float  RADIUS;				//�P�[�L�̔��a
	const double SCALE;					//�J�[�\���摜�̑傫��
	const double ANGLE;					//�J�[�\���摜�̉�]�l
	const VECTOR SIZE;					//���f���̔{��
	const VECTOR POSITION;				//���f���̈ʒu
	const VECTOR ROTATE;				//���f���̉�]�l
	const VECTOR INITIAL_WORLD_MOUSE;	//�����̃��[���h�}�E�X���W
	const string IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string CURSOR_PATH;			//�J�[�\���摜�̃p�X
};