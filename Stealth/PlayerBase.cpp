#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//�ړ����x
const VECTOR PlayerBase::POSITION = { 0.0f, 0.0f, 0.0f };		//���f���̈ʒu
const VECTOR PlayerBase::DIR	  = { 0.0f,0.0f,1.0f };			//���f���̌���

PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
{
	//�����Ȃ�
}

PlayerBase::~PlayerBase()
{
	//�����Ȃ�
}