#pragma once

#include <string>

/// <summary>
/// サウンド管理クラス
/// シングルトン
/// </summary>
class SoundManager final
{
public:
	SoundManager();
	virtual ~SoundManager();

	void Initialize();

	static SoundManager& GetInstance(); //アドレスを返す

	void PlayBgm(); //指定のBGMを再生開始
	void StopBgm();
	void DeleteBgm();

private:
	SoundManager(const SoundManager&);		//コピーコンストラクタ

	std::string InputPath(std::string folderPath,	//画像のパスを入力
						  std::string path);

	int bgmData[2];

	//静的定数
	static const std::string SOUND_FOLDER_PATH;		//soundフォルダまでのパス
	static const std::string GAME_BGM_PATH;			//ゲーム画面のBGM音のパス

};