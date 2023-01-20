#pragma once

#include "SceneBase.h"
#include <string>


using namespace std;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene final : public SceneBase
{
public:
	 TitleScene(SceneManager* const sceneManager);
	~TitleScene();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	//ゲーム状態
	enum class State
	{
		START,	//開始前
	};

private:

	TitleScene(const TitleScene&);		//コピーコンストラクタ

	void Blink();						//文字の点滅

	State state;
	int backGroundHandle;				//タイトル動画の格納用
	int titleName;						//タイトル名の画像格納用
	int titleUi;						//プレイシーンへ遷移キーのUI格納用
	int alpha;
	int inc;
	int prevAlpha;
	int frame;

	//静的定数
	static const string VIDEO_FOLDER_PATH;	//videoフォルダまでのパス
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string PLAY_VIDEO_PATH;	//タイトル動画のパス
	static const string TITLENAME_PATH;		//タイトル名の画像のパス
	static const string TITLE_UI_PATH;		//プレイシーンへ遷移キーのUIのパス

};