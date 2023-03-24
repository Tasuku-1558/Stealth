#include "FadeManager.h"
#include "PreCompiledHeader.h"
#include <math.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
FadeManager::FadeManager()
	: fade(0)
	, fadeInc(2)
	, BLACK(GetColor(0, 0, 0))
	, MAX_FADE(255)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FadeManager::~FadeManager()
{
	//�����Ȃ�
}

/// <summary>
/// ��ʌ��ʏ���
/// </summary>
void FadeManager::FadeMove()
{
	//��ʌ��ʂ̑����`�F�b�N
	if (fade > MAX_FADE && fadeInc > 0)
	{
		fadeInc *= -1;
	}

	fade += fadeInc;
}

/// <summary>
/// �`�揈��
/// </summary>
void FadeManager::Draw()
{
	//��ʑS�̃t�F�[�h�p�̋�`���F�̔w�i��`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);
}