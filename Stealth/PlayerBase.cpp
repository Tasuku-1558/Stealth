#include "PlayerBase.h"


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
	, playerFindImage(0)
	, findImageFlag(false)
	, spottedSeFlag(false)
	, SPEED(450.0f)
	, POSITION({ 0.0f, 0.0f, 0.0f })
	, DIR({ -1.0f,0.0f,0.0f })
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