#pragma once
#include "DxLib.h"

/// <summary>
/// ��ʌ��ʃN���X
/// </summary>
class FadeManager final
{
public:
	 FadeManager();
	 virtual ~FadeManager();

	void Activate();				//����������
	void FadeMove();				//��ʌ��ʏ���
	void Draw();					//�`�揈��

private:

	int fade;
	int fadeInc;
};