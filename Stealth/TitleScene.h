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
	 virtual ~TitleScene();

	void Initialize();					//初期化処理
	void Finalize();					//終了処理
	void Activate();					//活性化処理
	void Update(float deltaTime);		//更新処理
	void Draw();						//描画処理

	//ゲームの状態
	enum class State
	{
		START,	//開始前
	};

private:

	TitleScene(const TitleScene&);		//コピーコンストラクタ

	void Blink();						//文字の点滅処理

	State state;						//ゲームの状態
	int backGroundHandle;				//タイトル動画の格納用
	int titleName;						//タイトル名の画像格納用
	int titleUi;						//ステージ選択シーンへ遷移キーのUI格納用
	int alpha;
	int inc;
	int prevAlpha;
	int frame;

	//静的定数
	static const string VIDEO_FOLDER_PATH;	//videoフォルダまでのパス
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string PLAY_VIDEO_PATH;	//タイトル動画のパス
	static const string TITLENAME_PATH;		//タイトル名の画像のパス
	static const string TITLE_UI_PATH;		//ステージ選択シーンへ遷移キーのUIのパス

};