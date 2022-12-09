#pragma once

#include "DxLib.h"

class Player;

class Camera final
{
public:
	 Camera();	//�R���X�g���N�^
	~Camera();	//�f�X�g���N�^

	void Initialize();
	void Activate();
	void Update(Player* player);
	
private:

	VECTOR position;
	const float radius;
	float yaw;

	//�ÓI�萔
	static const float  NEAR_DISTANCE;		//�J�����ɉf���O�͈̔�
	static const float  FAR_DISTANCE;		//�J�����ɉf��ŉ��͈̔�
	static const VECTOR INITIAL_POSITION;	//�����ʒu
	static const VECTOR UP_VECTOR;			//�J�����̏����
};

