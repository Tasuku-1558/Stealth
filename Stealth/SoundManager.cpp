#include "SoundManager.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SoundManager::SoundManager()
	: bgmData()
	, seData()
	, sePlayFlag()
	, BGM_VOLUME(255 * 50 / 100)
	, SE_VOLUME(255 * 50 / 100)
	, SOUND_FOLDER_PATH("Data/Sound/")
	, BGM_PATH("bgm")
	, SE_PATH("se")
	, SOUND_FILENAME_EXTENSION(".mp3")
{
	LoadAllSound();
	VolumeAdjustment();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundManager::~SoundManager()
{
	DeleteAllSound();
}

/// <summary>
/// �A�h���X��Ԃ�
/// </summary>
/// <returns>soundManager��Ԃ�</returns>
SoundManager& SoundManager::GetInstance()
{
	static SoundManager soundManager;
	return soundManager;
}

/// <summary>
/// �S�ẴT�E���h�̓ǂݍ���
/// </summary>
void SoundManager::LoadAllSound()
{
	//BGM�̓ǂݍ���
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		string bgmPath = SOUND_FOLDER_PATH + BGM_PATH + to_string(i) + SOUND_FILENAME_EXTENSION;	// + �A�Ԑ��� + �g���q
		bgmData[i] = LoadSoundMem(bgmPath.c_str());

		if (bgmData[i] < 0)
		{
			printfDx("�����ǂݍ��݂Ɏ��s_SoundManager_bgm[%d]\n", i);
		}
	}

	//SE�̓ǂݍ���
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		string sePath = SOUND_FOLDER_PATH + SE_PATH + to_string(i) + SOUND_FILENAME_EXTENSION;	// + �A�Ԑ��� + �g���q
		seData[i] = LoadSoundMem(sePath.c_str());

		if (seData[i] < 0)
		{
			printfDx("�����ǂݍ��݂Ɏ��s_SoundManager_se[%d]\n", i);
		}
	}
}

/// <summary>
/// �S�ẴT�E���h�̍폜
/// </summary>
void SoundManager::DeleteAllSound()
{
	//BGM�̍폜
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		DeleteSoundMem(BGM_VOLUME, bgmData[i]);
		bgmData[i] = NULL;
	}

	//SE�̍폜
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		DeleteSoundMem(SE_VOLUME, seData[i]);
		seData[i] = NULL;
	}
}

/// <summary>
/// �T�E���h�̉��ʒ���
/// </summary>
void SoundManager::VolumeAdjustment()
{
	//BGM�̉��ʒ���
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		ChangeVolumeSoundMem(BGM_VOLUME, bgmData[i]);
	}

	//SE�̉��ʒ���
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
	}
}

/// <summary>
/// SE�X�V����
/// </summary>
void SoundManager::SeUpdate()
{
	//�o�^���ꂽSE���Đ�
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		//�o�^����Ă��Ȃ�
		if (!sePlayFlag[i])
		{
			continue;
		}

		//�������������ɍĐ����Ȃ��
		if (CheckSoundMem(seData[i]) != 0)
		{
			ChangeVolumeSoundMem(0, seData[i]);
			StopSoundMem(seData[i]);
			ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
		}

		PlaySoundMem(seData[i], DX_PLAYTYPE_BACK);		//SE���Đ�
		sePlayFlag[i] = false;
	}
}

/// <summary>
/// BGM���Đ�
/// </summary>
/// <param name="bgm">Bgm�̎��</param>
void SoundManager::PlayBgm(Bgm bgm)
{
	PlaySoundMem(bgmData[bgm], DX_PLAYTYPE_LOOP);
}

/// <summary>
/// BGM���~
/// </summary>
void SoundManager::StopBgm()
{
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		StopSoundMem(bgmData[i]);
	}
}

/// <summary>
/// SE���Đ����邩
/// </summary>
void SoundManager::SePlayFlag(Se se)
{
	sePlayFlag[se] = true;
}