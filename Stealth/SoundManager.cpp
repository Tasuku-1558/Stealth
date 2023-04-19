#include "SoundManager.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
SoundManager::~SoundManager()
{
	DeleteAllSound();
}

/// <summary>
/// アドレスを返す
/// </summary>
/// <returns>soundManagerを返す</returns>
SoundManager& SoundManager::GetInstance()
{
	static SoundManager soundManager;
	return soundManager;
}

/// <summary>
/// 全てのサウンドの読み込み
/// </summary>
void SoundManager::LoadAllSound()
{
	//BGMの読み込み
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		string bgmPath = SOUND_FOLDER_PATH + BGM_PATH + to_string(i) + SOUND_FILENAME_EXTENSION;	// + 連番数字 + 拡張子
		bgmData[i] = LoadSoundMem(bgmPath.c_str());

		if (bgmData[i] < 0)
		{
			printfDx("音声読み込みに失敗_SoundManager_bgm[%d]\n", i);
		}
	}

	//SEの読み込み
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		string sePath = SOUND_FOLDER_PATH + SE_PATH + to_string(i) + SOUND_FILENAME_EXTENSION;	// + 連番数字 + 拡張子
		seData[i] = LoadSoundMem(sePath.c_str());

		if (seData[i] < 0)
		{
			printfDx("音声読み込みに失敗_SoundManager_se[%d]\n", i);
		}
	}
}

/// <summary>
/// 全てのサウンドの削除
/// </summary>
void SoundManager::DeleteAllSound()
{
	//BGMの削除
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		DeleteSoundMem(BGM_VOLUME, bgmData[i]);
		bgmData[i] = NULL;
	}

	//SEの削除
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		DeleteSoundMem(SE_VOLUME, seData[i]);
		seData[i] = NULL;
	}
}

/// <summary>
/// サウンドの音量調整
/// </summary>
void SoundManager::VolumeAdjustment()
{
	//BGMの音量調整
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		ChangeVolumeSoundMem(BGM_VOLUME, bgmData[i]);
	}

	//SEの音量調整
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
	}
}

/// <summary>
/// SE更新処理
/// </summary>
void SoundManager::SeUpdate()
{
	//登録されたSEを再生
	for (int i = 0; i < SE_AMOUNT; ++i)
	{
		//登録されていない
		if (!sePlayFlag[i])
		{
			continue;
		}

		//同じ音声が既に再生中ならば
		if (CheckSoundMem(seData[i]) != 0)
		{
			ChangeVolumeSoundMem(0, seData[i]);
			StopSoundMem(seData[i]);
			ChangeVolumeSoundMem(SE_VOLUME, seData[i]);
		}

		PlaySoundMem(seData[i], DX_PLAYTYPE_BACK);		//SEを再生
		sePlayFlag[i] = false;
	}
}

/// <summary>
/// BGMを再生
/// </summary>
/// <param name="bgm">Bgmの種類</param>
void SoundManager::PlayBgm(Bgm bgm)
{
	PlaySoundMem(bgmData[bgm], DX_PLAYTYPE_LOOP);
}

/// <summary>
/// BGMを停止
/// </summary>
void SoundManager::StopBgm()
{
	for (int i = 0; i < BGM_AMOUNT; ++i)
	{
		StopSoundMem(bgmData[i]);
	}
}

/// <summary>
/// SEを再生するか
/// </summary>
void SoundManager::SePlayFlag(Se se)
{
	sePlayFlag[se] = true;
}