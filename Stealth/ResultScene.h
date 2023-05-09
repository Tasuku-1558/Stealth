#pragma once

#include <vector>
#include <string>
#include "SceneBase.h"
#include "DxLib.h"

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
	ResultScene(const ResultScene&);		//コピーコンストラクタ
	
	void Initialize()override;				//初期化処理
	void SceneChange();						//シーン切り替え
	void Blink();							//文字の点滅処理
	void BackGroundMove();					//背景画像の動き
	void ReturnScreen();					//画面を遷移する
	void InputScene(SceneType sceneType);	//シーンを入力
	void FireWorksParticlePop();			//花火パーティクルの出現

	Camera* camera;
	FireWorksParticle* fireWorksParticle;
	FadeManager* fadeManager;

	vector<FireWorksParticle*> activeFireWorksParticle;

	struct Particle
	{
		VECTOR position;		//パーティクルの位置
		unsigned int color;		//パーティクルのカラー
	};

	int resultFontHandle;	//ゲームフォント
	int resultUiImage;		//遷移キーのUi画像格納用
	int alpha;				//透過度
	int inc;				//透過スピード
	int backGroundImage;	//リザルト画面の背景格納用
	int backGroundPosY;		//背景のY座標
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら
	bool clear;				//ゲームをクリアしてるかしていないか
	bool titleFlag;			//タイトル画面へ遷移するかしないか
	bool selectionFlag;		//ステージセレクション画面へ遷移するかしないか


	//定数
	const int RESULT_FONT_SIZE;				//ゲームフォントのサイズ
	const int FONT_THICK;					//フォントの太さ
	const int PARTICLE_NUMBER;				//パーティクルの数
	const int PARTICLE_CATEGORY;			//パーティクルの種類
	const int MAX_ALPHA;					//最大透過度
	const int INC_SPEED;					//透過スピード
	const int RESULT_UI_POS_X;				//遷移キーのUi画像のX座標
	const int RESULT_UI_POS_Y;				//遷移キーのUi画像のY座標
	const int BACKGROUND_POS_X;				//背景のX座標
	const int BACKGROUND_Y_INCREASE;		//背景のY座標の増加量
	const int INITIAL_BACKGROUND_POS_Y;		//初期のY座標
	const int RESULT_STRING_POS_X;			//リザルト文字のX座標
	const int RESULT_STRING_POS_Y;			//リザルト文字のY座標

	const unsigned int GAME_CLEAR_COLOR;		//ゲームクリアのカラー
	const unsigned int GAME_OVER_COLOR;			//ゲームオーバーのカラー
	const unsigned int YELLOW_PARTICLE_COLOR;	//黄色のパーティクルのカラー
	const unsigned int GREEN_PARTICLE_COLOR;	//緑色のパーティクルのカラー
	const unsigned int RED_PARTICLE_COLOR;		//赤色のパーティクルのカラー

	const float MAX_PARTICLE_INTERVAL;		//パーティクル出現の最大インターバル
	const float PARTICLE_INTERVAL;			//初期のパーティクル出現インターバル

	const double RESULT_UI_SIZE;			//遷移キーのUi画像の大きさ
	const double RESULT_UI_ANGLE;			//遷移キーのUi画像の回転値

	const char GAME_CLEAR[11];				//ゲームクリアの文字
	const char GAME_OVER[10];				//ゲームオーバーの文字

	const VECTOR YELLOW_PARTICLE_POSITION;	//黄色のパーティクルの位置
	const VECTOR GREEN_PARTICLE_POSITION;	//緑色のパーティクルの位置
	const VECTOR RED_PARTICLE_POSITION;		//赤色のパーティクルの位置

	const string IMAGE_FOLDER_PATH;			//Imageフォルダまでのパス
	const string RESULT_UI_PATH;			//リザルト画面のUiのパス
	const string RESULT_BACKGROUND_PATH;	//リザルト画面の背景画像のパス
};