#pragma once

#include "SceneBase.h"
#include "DxLib.h"
#include <string>

class Light;
class Camera;
class FadeManager;

using namespace std;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene final : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	SceneType Update(float deltaTime)override;		//更新処理
	void Draw()override;							//描画処理

private:

	TitleScene(const TitleScene&);		//コピーコンストラクタ

	void Initialize()override;			//初期化処理
	void Blink();						//文字の点滅処理
	void ChangeState();					//タイトルの状態の変更

	string InputPath(string folderPath,
					 string path);		//画像のパスを入力

	//タイトルの状態
	enum class TitleState
	{
		START,	//ゲームを始める
		EXIT,	//ゲームを終了する
	};

	TitleState titleState;				//タイトルの状態
	int titleMovie;						//タイトル動画の格納用
	int titleName;						//タイトル名の画像格納用
	int startUi;						//ゲームを始める遷移キーのUI格納用
	int exitUi;							//ゲームを終了する遷移キーのUI格納用
	int alpha;							//透過度
	int inc;
	float frame;						//フレーム数
	VECTOR spherePosition;				//3D球体の位置

	Light* light;						//ライトクラスのポインタ
	Camera* camera;						//カメラクラスのポインタ
	FadeManager* fadeManager;			//フェードマネージャークラスのポインタ


	//定数
	const string VIDEO_FOLDER_PATH;	//Videoフォルダまでのパス
	const string IMAGE_FOLDER_PATH;	//Imageフォルダまでのパス
	const string PLAY_VIDEO_PATH;	//タイトル動画のパス
	const string TITLENAME_PATH;	//タイトル名の画像のパス
	const string START_UI_PATH;		//ゲームを始める遷移キーのUIのパス
	const string EXIT_UI_PATH;		//ゲームを終了する遷移キーのUIのパス
	const int	 MAX_ALPHA;			//最大透過度
	const int	 PLAY_POSITION;		//タイトル動画の再生位置
	const float  START_SPHERE_POS_Z;//スタート状態の球のZ座標
	const float  EXIT_SPHERE_POS_Z;	//終了状態の球のZ座標

};