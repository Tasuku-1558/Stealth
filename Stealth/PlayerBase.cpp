#include "PlayerBase.h"


const float  PlayerBase::SPEED	  = 500.0f;						//�ړ����x
const VECTOR PlayerBase::POSITION = { 0.0f, 0.0f, 0.0f };		//���f���̈ʒu
const VECTOR PlayerBase::DIR	  = { -1.0f,0.0f,0.0f };		//���f���̌���

//const VECTOR PlayerBase::UP	  = { 1, 0, 0};					//�����
//const VECTOR PlayerBase::DOWN	  = {-1, 0, 0};					//������
//const VECTOR PlayerBase::LEFT	  = { 0, 0, -1};				//������
//const VECTOR PlayerBase::RIGHT  = { 0, 0,1};					//�E����


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerBase::PlayerBase()
	: inputDirection()
	, inputFlag(false)
	, speed(0.0f)
	, previewPosition()
	, playerFindCount(0)
	, spottedSe(0)
	, spottedSeFlag(false)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBase::~PlayerBase()
{
	//�����Ȃ�
}