#pragma once

#include "DxLib.h"
#include "Math3D.h"


/// <summary>
/// �J�����N���X(�Œ�^�J����)
/// </summary>
class Camera final
{
public:
	 Camera();
	 virtual ~Camera();

	void Initialize();						//����������
	void Update(VECTOR pos);				//�X�V����

	VECTOR GetUp()	  { return up; }
	VECTOR GetDown()  { return down; }
	VECTOR GetRight() { return right; }
	VECTOR GetLeft()  { return left; }
	
private:

	VECTOR position;		//�J�����̈ʒu
	VECTOR front;
	const float radius;		//�J������]���a
	float yaw;				//�J������]�p
	float angleY;
	
	VECTOR up;				//�����
	VECTOR down;			//������
	VECTOR right;			//�E����
	VECTOR left;			//������

	//�ÓI�萔
	static const float  NEAR_DISTANCE;		//�J�����ɉf���O�͈̔�
	static const float  FAR_DISTANCE;		//�J�����ɉf��ŉ��͈̔�
	//static const VECTOR INITIAL_POSITION;	//�����ʒu
	//static const VECTOR UP_VECTOR;		//�J�����̏����
};

