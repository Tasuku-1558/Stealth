#pragma once

#include <vector>
#include <string>
#include "SceneBase.h"
#include "DxLib.h"

class Camera;
class FireWorksParticle;
class FadeManager;

using namespace std;

/// <summary>
/// ���U���g�V�[���N���X
/// </summary>
class ResultScene final : public SceneBase
{
public:
	ResultScene();
	virtual ~ResultScene();

	SceneType Update(float deltaTime)override;	//�X�V����
	void Draw()override;						//�`�揈��

private:
	ResultScene(const ResultScene&);		//�R�s�[�R���X�g���N�^
	
	void Initialize()override;				//����������
	void SceneChange();						//�V�[���؂�ւ�
	void Blink();							//�����̓_�ŏ���
	void BackGroundMove();					//�w�i�摜�̓���
	void ReturnScreen();					//��ʂ�J�ڂ���
	void InputScene(SceneType sceneType);	//�V�[�������
	void FireWorksParticlePop();			//�ԉ΃p�[�e�B�N���̏o��

	Camera* camera;
	FireWorksParticle* fireWorksParticle;
	FadeManager* fadeManager;

	vector<FireWorksParticle*> activeFireWorksParticle;

	struct Particle
	{
		VECTOR position;		//�p�[�e�B�N���̈ʒu
		unsigned int color;		//�p�[�e�B�N���̃J���[
	};

	int resultFontHandle;	//�Q�[���t�H���g
	int resultUiImage;		//�J�ڃL�[��Ui�摜�i�[�p
	int alpha;				//���ߓx
	int inc;				//���߃X�s�[�h
	int backGroundImage;	//���U���g��ʂ̔w�i�i�[�p
	int backGroundPosY;		//�w�i��Y���W
	float frame;			//�t���[����
	float particleInterval;	//�p�[�e�B�N���o���̃C���^�[�o��
	bool  particleFlag;		//�p�[�e�B�N�����o������
	bool clear;				//�Q�[�����N���A���Ă邩���Ă��Ȃ���
	bool titleFlag;			//�^�C�g����ʂ֑J�ڂ��邩���Ȃ���
	bool selectionFlag;		//�X�e�[�W�Z���N�V������ʂ֑J�ڂ��邩���Ȃ���


	//�萔
	const int RESULT_FONT_SIZE;				//�Q�[���t�H���g�̃T�C�Y
	const int FONT_THICK;					//�t�H���g�̑���
	const int PARTICLE_NUMBER;				//�p�[�e�B�N���̐�
	const int PARTICLE_CATEGORY;			//�p�[�e�B�N���̎��
	const int MAX_ALPHA;					//�ő哧�ߓx
	const int INC_SPEED;					//���߃X�s�[�h
	const int RESULT_UI_POS_X;				//�J�ڃL�[��Ui�摜��X���W
	const int RESULT_UI_POS_Y;				//�J�ڃL�[��Ui�摜��Y���W
	const int BACKGROUND_POS_X;				//�w�i��X���W
	const int BACKGROUND_Y_INCREASE;		//�w�i��Y���W�̑�����
	const int INITIAL_BACKGROUND_POS_Y;		//������Y���W
	const int RESULT_STRING_POS_X;			//���U���g������X���W
	const int RESULT_STRING_POS_Y;			//���U���g������Y���W

	const unsigned int GAME_CLEAR_COLOR;		//�Q�[���N���A�̃J���[
	const unsigned int GAME_OVER_COLOR;			//�Q�[���I�[�o�[�̃J���[
	const unsigned int YELLOW_PARTICLE_COLOR;	//���F�̃p�[�e�B�N���̃J���[
	const unsigned int GREEN_PARTICLE_COLOR;	//�ΐF�̃p�[�e�B�N���̃J���[
	const unsigned int RED_PARTICLE_COLOR;		//�ԐF�̃p�[�e�B�N���̃J���[

	const float MAX_PARTICLE_INTERVAL;		//�p�[�e�B�N���o���̍ő�C���^�[�o��
	const float PARTICLE_INTERVAL;			//�����̃p�[�e�B�N���o���C���^�[�o��

	const double RESULT_UI_SIZE;			//�J�ڃL�[��Ui�摜�̑傫��
	const double RESULT_UI_ANGLE;			//�J�ڃL�[��Ui�摜�̉�]�l

	const char GAME_CLEAR[11];				//�Q�[���N���A�̕���
	const char GAME_OVER[10];				//�Q�[���I�[�o�[�̕���

	const VECTOR YELLOW_PARTICLE_POSITION;	//���F�̃p�[�e�B�N���̈ʒu
	const VECTOR GREEN_PARTICLE_POSITION;	//�ΐF�̃p�[�e�B�N���̈ʒu
	const VECTOR RED_PARTICLE_POSITION;		//�ԐF�̃p�[�e�B�N���̈ʒu

	const string IMAGE_FOLDER_PATH;			//Image�t�H���_�܂ł̃p�X
	const string RESULT_UI_PATH;			//���U���g��ʂ�Ui�̃p�X
	const string RESULT_BACKGROUND_PATH;	//���U���g��ʂ̔w�i�摜�̃p�X
};