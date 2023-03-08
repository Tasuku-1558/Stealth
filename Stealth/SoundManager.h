#pragma once

#include <string>

using namespace std;

/// <summary>
/// �T�E���h�Ǘ��N���X
/// BGM��SE�̍Đ��ƒ�~���s��
/// �V���O���g��
/// </summary>
class SoundManager final
{
public:

	//BGM�̎��
	enum Bgm
	{
		TITLE,		//�^�C�g����
		/*PLAY,
		RESULT,*/
		BGM_AMOUNT	//BGM�̐�
	};

	//SE�̎��
	enum Se
	{
		ENEMY_FIND,	//�G�l�~�[�Ɍ�����������SE
		CAKE_SHOOT,	//�P�[�L�𔭎˂�������SE
		SE_AMOUNT	//SE�̐�
	};

	static SoundManager& GetInstance();		//�A�h���X��Ԃ�

	void SeUpdate();						//SE�X�V����
	void PlayBgm(Bgm bgm);					//BGM���Đ�
	void StopBgm();							//BGM���~
	void SePlayFlag(Se se);					//SE���Đ����邩

private:
	SoundManager();
	SoundManager(const SoundManager&);		//�R�s�[�R���X�g���N�^
	virtual ~SoundManager();

	void LoadAllSound();					//�S�ẴT�E���h�̓ǂݍ���
	void DeleteAllSound();					//�S�ẴT�E���h�̍폜
	void VolumeAdjustment();				//�T�E���h�̉��ʒ���

	int  bgmData[BGM_AMOUNT];				//BGM�ǂݍ���
	int	 seData[SE_AMOUNT];					//SE�ǂݍ���
	bool sePlayFlag[SE_AMOUNT];				//SE���Đ����邩


	//�萔
	const string SOUND_FOLDER_PATH;			//sound�t�H���_�܂ł̃p�X
	const string BGM_PATH;					//BGM�t�H���_�܂ł̃p�X
	const string SE_PATH;					//SE�t�H���_�܂ł̃p�X
	const string SOUND_FILENAME_EXTENSION;	//BGM��SE�̊g���q
	const int	 BGM_VOLUME;				//BGM�̉���
	const int	 SE_VOLUME;					//SE�̉���

};