#pragma once

#include "SceneBase.h"
#include <string>

using namespace std;

class Camera;
class FadeManager;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene final : public SceneBase
{
public:
	TitleScene(SceneManager* const sceneManager);
	virtual ~TitleScene();

	void Initialize()override;					//初期化処理
	void Activate()override;					//活性化処理
	void Update(float deltaTime)override;		//更新処理
	void Draw()override;						//描画処理

private:

	TitleScene(const TitleScene&);		//コピーコンストラクタ

	string InputPath(string folderPath,	//画像のパスを入力
					 string path);

	void Blink();						//文字の点滅処理
	void Finalize()override;			//終了処理
	void ChangeState();					//タイトルの状態の変更

	//タイトルの状態
	enum class SelectState
	{
		START,	//ゲームを始める
		EXIT,	//ゲームを終了する
	};

	SelectState selectState;			//タイトルの状態

	int titleMovie;						//タイトル動画の格納用
	int titleName;						//タイトル名の画像格納用
	int titleUi;						//ステージ選択シーンへ遷移キーのUI格納用
	int alpha;							//透過度
	int inc;
	float frame;						//フレーム数
	float sphereZ;						//選択状態の目印球

	Camera* camera;						//カメラクラスのポインタ
	FadeManager* fadeManager;			//フェードマネージャークラスのポインタ

	//定数
	const string VIDEO_FOLDER_PATH;	//videoフォルダまでのパス
	const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	const string PLAY_VIDEO_PATH;	//タイトル動画のパス
	const string TITLENAME_PATH;	//タイトル名の画像のパス
	const string TITLE_UI_PATH;		//ステージ選択シーンへ遷移キーのUIのパス

};