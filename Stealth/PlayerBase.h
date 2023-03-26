#pragma once

#include "ObjectBase.h"
#include <string>


/// <summary>
/// �v���C���[���N���X
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

protected:

	VECTOR inputDirection;		//���͂��ꂽ����
	VECTOR nextPosition;		//�����̃v���C���[�̈ʒu
	int	   playerFindCount;		//�G�l�~�[�Ɍ��������񐔂𐔂���
	int	   playerFindImage;		//�G�l�~�[�Ɍ��������摜�i�[�p
	int	   findImageX;			//���������摜��X���W
	int    findImageY;			//���������摜��Y���W
	float  speed;				//�ړ����x
	float  initialTime;			//�v���C���[�̏������������鎞��
	bool   inputFlag;			//�L�[���̓t���O
	bool   findImageFlag;		//�G�l�~�[�Ɍ��������摜��\�����邩���Ȃ���
	bool   spottedSeFlag;		//�G�l�~�[�Ɍ�����������SE���𗬂��������Ȃ���


	//�萔
	const float	  SPEED;						//�ړ����x
	const float	  OPACITY;						//�s�����x
	const float	  RADIUS;						//�v���C���[�̔��a
	const VECTOR  POSITION;						//���f���̈ʒu
	const VECTOR  DIRECTION;					//���f���̌���
	const VECTOR  UP;							//�����
	const VECTOR  DOWN;							//������
	const VECTOR  LEFT;							//������
	const VECTOR  RIGHT;						//�E����
	const VECTOR  AFTER_IMAGE_ADJUSTMENT;		//�c���̒����l
	const COLOR_F AFTER_IMAGE_COLOR;			//�c�����f���̃G�~�b�V�u�J���[
};