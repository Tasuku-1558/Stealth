#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 400.0f;						//�ړ����x
const VECTOR PlayerBase::POSITION = VGet(0.0f, 200.0f, 150.0f);	//���f���̈ʒu

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