#pragma once

#include "SceneBase.h"
#include <vector>
#include <string>

class Camera;
class FireWorksParticle;
class FadeManager;

using namespace std;


/// <summary>
/// リザルトシーン
/// </summary>
class ResultScene final : public SceneBase
{
public:

	ResultScene(SceneManager* const sceneManager);
	virtual ~ResultScene();

	void Initialize();					//初期化処理
	void Activate();					//活性化処理
	void Update(float deltaTime);		//更新処理
	void Draw();						//描画処理

private:
	ResultScene(const ResultScene&);	//コピーコンストラクタ
	
	void Finalize();								//終了処理
	void SceneChange();								//シーン切り替え
	void Blink();									//文字の点滅処理
	void BackGroundMove();							//背景画像の動き
	void ReturnScreen(float deltaTime);				//画面を遷移する

	string InputPath(string folderPath,	//画像のパスを入力
					 string path);

	void EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle);		//花火パーティクルを登録
	void DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle);	//花火パーティクルを削除
	void FireWorksParticlePop();												//花火パーティクルの出現

	Camera* camera;
	vector<FireWorksParticle*> fireWorksParticle;
	FadeManager* fadeManager;


	int font;				//ゲームフォント
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら
	int resultUiImage;		//リザルト画面のUI画像格納用
	bool clear;
	int alpha;
	int inc;
	int prevAlpha;
	bool title;				//タイトル画面へ遷移するかしないか
	bool selection;			//ステージセレクション画面へ遷移するかしないか
	int backGroundImage;	//リザルト画面の背景格納用
	int backGroundX;		//背景のX座標
	int backGroundY;		//背景のY座標

	//静的定数
	static const string IMAGE_FOLDER_PATH;		//imageフォルダまでのパス
	static const string RESULT_UI_PATH;			//リザルト画面のUIのパス
	static const string RESULT_BACKGROUND_PATH;	//リザルト画面の背景画像のパス
	static const int    PARTICLE_NUMBER;		//パーティクルの数

};