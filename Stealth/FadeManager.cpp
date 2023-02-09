#include "FadeManager.h"
#include "PreCompiledHeader.h"
#include <math.h>


const int FadeManager::BLACK = GetColor(0, 0, 0);	//�t�F�[�h�̃J���[

/// <summary>
/// �R���X�g���N�^
/// </summary>
FadeManager::FadeManager()
	: fade(0)
	, fadeInc(3)
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
/// ����������
/// </summary>
void FadeManager::Activate()
{
	fade = 0;
	fadeInc = 2;
}

/// <summary>
/// ��ʌ��ʏ���
/// </summary>
void FadeManager::FadeMove()
{
	//��ʌ��ʂ̑����`�F�b�N
	if (fade > 255 && fadeInc > 0)
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
	//��ʑS�̃t�F�[�h�p�̋�`�������`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fade);
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, fade);
}