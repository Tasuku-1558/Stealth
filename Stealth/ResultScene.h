#pragma once

#include "SceneBase.h"
#include <vector>
#include <string>

class Camera;
class FireWorksParticle;
class FadeManager;

using namespace std;

/// <summary>
/// リザルトシーンクラス
/// </summary>
class ResultScene final : public SceneBase
{
public:

	ResultScene();
	virtual ~ResultScene();

	SceneType Update(float deltaTime)override;	//更新処理
	void Draw()override;						//描画処理

private:
	ResultScene(const ResultScene&);	//コピーコンストラクタ
	
	void Initialize()override;				//初期化処理
	void SceneChange();						//シーン切り替え
	void Blink();							//文字の点滅処理
	void BackGroundMove();					//背景画像の動き
	void ReturnScreen();					//画面を遷移する
	void InputScene(SceneType sceneType);	//シーンを入力

	string InputPath(string folderPath,	//画像のパスを入力
					 string path);

	void EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle);		//花火パーティクルを登録
	void DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle);	//花火パーティクルを削除
	void FireWorksParticlePop();												//花火パーティクルの出現

	Camera* camera;
	vector<FireWorksParticle*> fireWorksParticle;
	FadeManager* fadeManager;


	int fontHandle;			//ゲームフォント
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら
	int resultUiImage;		//リザルト画面のUI画像格納用
	bool clear;
	int alpha;				//透過度
	int inc;
	int prevAlpha;
	bool titleFlag;			//タイトル画面へ遷移するかしないか
	bool selectionFlag;		//ステージセレクション画面へ遷移するかしないか
	int backGroundImage;	//リザルト画面の背景格納用
	int backGroundX;		//背景のX座標
	int backGroundY;		//背景のY座標


	//定数
	const string IMAGE_FOLDER_PATH;			//Imageフォルダまでのパス
	const string RESULT_UI_PATH;			//リザルト画面のUIのパス
	const string RESULT_BACKGROUND_PATH;	//リザルト画面の背景画像のパス
	const int    PARTICLE_NUMBER;			//パーティクルの数
};