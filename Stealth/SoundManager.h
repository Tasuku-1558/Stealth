#pragma once

#include <string>

using namespace std;

/// <summary>
/// サウンド管理クラス
/// シングルトン
/// </summary>
class SoundManager final
{
public:

	//BGMの種類
	enum Bgm
	{
		TITLE,		//タイトル曲
		GAME,		//ゲーム曲
		RESULT,		//リザルト曲
		BGM_AMOUNT	//BGMの数
	};

	//SEの種類
	enum Se
	{
		ENEMY_FIND,	//エネミーに見つかった時のSE
		CAKE_SHOOT,	//ケーキを発射した時のSE
		SE_AMOUNT	//SEの数
	};

	static SoundManager& GetInstance();		//アドレスを返す

	void SeUpdate();						//SE更新処理
	void PlayBgm(Bgm bgm);					//BGMを再生
	void StopBgm();							//BGMを停止
	void SePlayFlag(Se se);					//SEを再生するか

private:
	SoundManager();
	SoundManager(const SoundManager&);		//コピーコンストラクタ
	virtual ~SoundManager();

	void LoadAllSound();					//全てのサウンドの読み込み
	void DeleteAllSound();					//全てのサウンドの削除
	void VolumeAdjustment();				//サウンドの音量調整

	int  bgmData[BGM_AMOUNT];				//BGM読み込み
	int	 seData[SE_AMOUNT];					//SE読み込み
	bool sePlayFlag[SE_AMOUNT];				//SEを再生するか


	//定数
	const int	 BGM_VOLUME;				//BGMの音量
	const int	 SE_VOLUME;					//SEの音量
	const string SOUND_FOLDER_PATH;			//Soundフォルダまでのパス
	const string BGM_PATH;					//BGMフォルダまでのパス
	const string SE_PATH;					//SEフォルダまでのパス
	const string SOUND_FILENAME_EXTENSION;	//BGMとSEの拡張子

};