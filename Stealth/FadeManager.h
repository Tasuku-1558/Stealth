#pragma once

/// <summary>
/// ��ʌ��ʃN���X
/// </summary>
class FadeManager final
{
public:
	FadeManager();
	virtual ~FadeManager();

	void FadeMove();	//��ʌ��ʏ���
	void Draw();		//�`�揈��

	const bool FadeEnd() { return fadeEnd; }		//�t�F�[�h���I����������Ԃ�

private:
	FadeManager(const FadeManager&);	//�R�s�[�R���X�g���N�^

	int fade;		//��ʌ��ʒl
	int fadeInc;	//��ʌ��ʃX�s�[�h�l
	bool fadeEnd;	//��ʌ��ʏI���t���O

	//�萔
	const int TOP_LEFT_VERTEX_X;	//����̒��_X���W
	const int TOP_LEFT_VERTEX_Y;	//����̒��_Y���W
	const int BLACK;				//�t�F�[�h�̃J���[
	const int MAX_FADE;				//�ő�t�F�[�h�l
	const int FADE_SPEED;			//�t�F�[�h�̃X�s�[�h

};