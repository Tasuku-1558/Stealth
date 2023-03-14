#pragma once

#include "DxLib.h"
#include "Math3D.h"


/// <summary>
/// �J�����N���X
/// �v���C���[�ւ̒Ǐ]�J����
/// </summary>
class Camera final
{
public:
	Camera();
	virtual ~Camera();

	void Update(VECTOR playerPosition);			//�X�V����
	void SelectionAndResultCamera();			//�X�e�[�W�Z���N�V������ʂƃ��U���g��ʂ̃J����

private:
	Camera(const Camera&);						//�R�s�[�R���X�g���N�^

	void Initialize();							//����������

	VECTOR position;		//�J�����̈ʒu
	VECTOR cameraOffset;	//�v���C���[����̑��Έʒu
	VECTOR lookPos;			//�J�����̒����_
	VECTOR aimLookPos;
	VECTOR aimCameraPos;
	VECTOR lookMoveDir;
	VECTOR posMoveDir;

	//�萔
	const float  NEAR_DISTANCE;		//�J�����ɉf���O�͈̔�
	const float  FAR_DISTANCE;		//�J�����ɉf��ŉ��͈̔�
	const VECTOR INITIAL_POSITION;	//�����ʒu
	const VECTOR UP_VECTOR;			//�J�����̏����
};

