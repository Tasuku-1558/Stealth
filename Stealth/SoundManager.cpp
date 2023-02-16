#include "SoundManager.h"
#include "DxLib.h"


using std::string; // �g�����̂���using�錾


const string SoundManager::SOUND_FOLDER_PATH = "data/sound/";		//sound�t�H���_�܂ł̃p�X
const string SoundManager::GAME_BGM_PATH = "gameBgm.mp3";	//�Q�[����ʂ�BGM���̃p�X


SoundManager::SoundManager()
	: bgmData()
{
	Initialize();
}

SoundManager::~SoundManager()
{
}

void SoundManager::Initialize()
{
	bgmData[0] = LoadSoundMem(InputPath(SOUND_FOLDER_PATH, GAME_BGM_PATH).c_str());
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager soundManager;
	return soundManager;
}

string SoundManager::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

void SoundManager::PlayBgm()
{
	PlaySoundMem(bgmData[0], DX_PLAYTYPE_LOOP, TRUE);
}

void SoundManager::StopBgm()
{
	StopSoundMem(bgmData[0]);
}

void SoundManager::DeleteBgm()
{
	DeleteSoundMem(bgmData[0]);
}