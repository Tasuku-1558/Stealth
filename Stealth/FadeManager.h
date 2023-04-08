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

	const bool FadeEnd() { return fadeEnd; }		//�t�F�[�h���I����������Ԃ�

private:
	FadeManager(const FadeManager&);	//�R�s�[�R���X�g���N�^

	int fade;			//�t�F�[�h�l
	int fadeInc;
	bool fadeEnd;		//�t�F�[�h�I���t���O

	//�萔
	const int BLACK;		//�t�F�[�h�̃J���[
	const int MAX_FADE;		//�ő�t�F�[�h�l
};