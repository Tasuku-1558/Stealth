#pragma once

/// <summary>
/// ��ʌ��ʃN���X
/// </summary>
class FadeManager final
{
public:
	FadeManager();
	virtual ~FadeManager();

	void FadeMove();					//��ʌ��ʏ���
	void Draw();						//�`�揈��

private:
	FadeManager(const FadeManager&);	//�R�s�[�R���X�g���N�^

	int fade;
	int fadeInc;

	//�萔
	const int BLACK;			//�t�F�[�h�̃J���[
	const int MAX_FADE;
};