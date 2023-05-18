#pragma once

#include <string>
#include "ObjectBase.h"

using namespace std;

/// <summary>
/// �v���C���[���N���X
/// </summary>
class PlayerBase : public ObjectBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

protected:

	int	   playerFindCount;		//�G�l�~�[�Ɍ��������񐔂𐔂���
	int	   playerFindImage;		//�G�l�~�[�Ɍ��������摜�i�[�p
	int	   afterImageModel[12];	//�c�����f���i�[�p
	float  speed;				//�ړ����x
	float  initialTime;			//�����ʒu�ɖ߂��J�E���g
	bool   inputFlag;			//�L�[���̓t���O
	bool   findImageFlag;		//�G�l�~�[�Ɍ��������摜��\�����邩���Ȃ���
	bool   spottedSeFlag;		//�G�l�~�[�Ɍ�����������SE���𗬂��������Ȃ���
	VECTOR inputDirection;		//���͂��ꂽ����
	VECTOR nextPosition;		//�����̃v���C���[�̈ʒu
	VECTOR pastPosition[12];	//�v���C���[�̉ߋ��̈ʒu

	//�萔
	const int	  FIND_IMAGE_X;				//���������摜��X���W
	const int	  FIND_IMAGE_Y;				//���������摜��Y���W
	const int	  AFTER_IMAGE_NUMBER;		//�v���C���[�̎c������
	const int	  MATERIAL_INDEX;			//�G�~�b�V�u�J���[��ύX����}�e���A���̔ԍ�
	const int	  KEY_INPUT_PATTERN;		//�L�[���̓p�^�[��

	const float	  INITIAL_SPEED;			//�����̈ړ����x
	const float	  OPACITY;					//�s�����x
	const float	  RADIUS;					//���a
	const float	  Y_ANGLE;					//Y���̉�]�l
	const float   MAX_INITIAL_TIME;			//�����ʒu�ɖ߂��ő�J�E���g
	const float	  INITIAL_TIME;				//�����ʒu�ɖ߂��J�E���g
	const float   STOP_SPEED;				//�v���C���[�̈ړ����x���~������
	const float	  MAX_INPUT_DIRECTION;		//�ő�̓��͂��ꂽ����

	const VECTOR  INITIAL_POSITION;			//�����̃v���C���[�̈ʒu
	const VECTOR  INITIAL_DIRECTION;		//�����̃v���C���[�̌���
	const VECTOR  UP;						//�����
	const VECTOR  DOWN;						//������
	const VECTOR  LEFT;						//������
	const VECTOR  RIGHT;					//�E����
	const VECTOR  AFTER_IMAGE_ADJUSTMENT;	//�c���̒����l

	const string  IMAGE_FOLDER_PATH;		//Image�t�H���_�܂ł̃p�X
	const string  PLAYER_FIND_PATH;			//�G�l�~�[�Ɍ����������̉摜�̃p�X

	const COLOR_F AFTER_IMAGE_COLOR;		//�c�����f���̃G�~�b�V�u�J���[

private:
	PlayerBase(const PlayerBase&);			//�R�s�[�R���X�g���N�^
};