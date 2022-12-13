#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 500.0f;						//�ړ����x
const int	 PlayerBase::HP		  = 50;							//�v���C���[��HP
const VECTOR PlayerBase::POSITION = { 3800.0f, 0.0f, -540.0f };		//���f���̈ʒu
const VECTOR PlayerBase::DIR	  = { -1.0f,0.0f,0.0f };			//���f���̌���
const VECTOR PlayerBase::UP		  = { -1,  0,  0};				//�����
const VECTOR PlayerBase::DOWN	  = { 1,  0, 0};				//������
const VECTOR PlayerBase::LEFT	  = {0,  0,  -1};				//������
const VECTOR PlayerBase::RIGHT	  = { 0,  0,  1};				//�E����


PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
	, hp(0)
{
	//�����Ȃ�
}

PlayerBase::~PlayerBase()
{
	//�����Ȃ�
}