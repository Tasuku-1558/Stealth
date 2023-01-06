#pragma once

#include "DxLib.h"
#include "Math3D.h"

class Player;


/// <summary>
/// �J�����N���X
/// </summary>
class Camera final
{
public:
	 Camera();	//�R���X�g���N�^
	~Camera();	//�f�X�g���N�^

	void Initialize();
	void Update(Player* player);

	VECTOR GetUp()	  { return up; }
	VECTOR GetDown()  { return down; }
	VECTOR GetRight() { return right; }
	VECTOR GetLeft()  { return left; }
	
private:

	VECTOR position;		//�J�����̈ʒu
	VECTOR front;
	const float radius;		//�J������]���a
	float yaw;				//�J������]�p
	
	VECTOR up;				//�����
	VECTOR down;			//������
	VECTOR right;			//�E����
	VECTOR left;			//������

	//�ÓI�萔
	static const float  NEAR_DISTANCE;		//�J�����ɉf���O�͈̔�
	static const float  FAR_DISTANCE;		//�J�����ɉf��ŉ��͈̔�
	static const float  ROTATING_VELOCITY;	//�J�����̉�]���x
	static const VECTOR INITIAL_POSITION;	//�����ʒu
	static const VECTOR UP_VECTOR;			//�J�����̏����
};

