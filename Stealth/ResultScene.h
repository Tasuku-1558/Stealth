#pragma once

#include "SceneBase.h"
#include <vector>

class FireWorksParticle;
class FadeManager;

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
	
	void Finalize();					//終了処理
	void SceneChange();					//シーン切り替え

	void EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle);		//花火パーティクルを登録
	void DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle);	//花火パーティクルを削除
	void FireWorksParticlePop();												//花火パーティクルの出現

	void UpdateGame(float deltaTime);				//ゲーム中
	void ReturnTitle(float deltaTime);				//タイトル画面へ
	void ReturnSelection(float deltaTime);			//セレクション画面へ
	void ReturnStage(float deltaTime);				//もう一度プレイ
	void (ResultScene::* pUpdate)(float deltaTime);	//Update関数ポインタ


	std::vector<FireWorksParticle*> fireWorksParticle;
	FadeManager* fadeManager;



	int font;				//ゲームフォント
	float frame;			//フレーム数
	float particleInterval;	//パーティクル出現のインターバル
	bool  particleFlag;		//パーティクルを出したら

};