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

	void Initialize();							//����������
	void Update(VECTOR pos);					//�X�V����
	void SelectionCamera();						//�X�e�[�W�Z���N�V������ʗp�J����

	const VECTOR GetUp()	{ return up; }		//�J�����̏������Ԃ�
	const VECTOR GetDown()  { return down; }	//�J�����̉�������Ԃ�
	const VECTOR GetRight() { return right; }	//�J�����̉E������Ԃ�
	const VECTOR GetLeft()  { return left; }	//�J�����̍�������Ԃ�
	
private:

	VECTOR position;		//�J�����̈ʒu
	VECTOR front;
	const float radius;		//�J������]���a
	float yaw;				//�J������]�p
	float angleY;
	
	VECTOR up;				//�J�����̏����
	VECTOR down;			//�J�����̉�����
	VECTOR right;			//�J�����̉E����
	VECTOR left;			//�J�����̍�����

	//�ÓI�萔
	static const float  NEAR_DISTANCE;		//�J�����ɉf���O�͈̔�
	static const float  FAR_DISTANCE;		//�J�����ɉf��ŉ��͈̔�
	static const VECTOR INITIAL_POSITION;	//�����ʒu
	static const VECTOR UP_VECTOR;			//�J�����̏����
};

