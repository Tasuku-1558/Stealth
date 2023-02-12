#pragma once

#include "SceneBase.h"

class FireWorksParticle;

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
	ResultScene(const ResultScene&);		//コピーコンストラクタ
	
	void Finalize();					//終了処理

	FireWorksParticle* fireWorksParticle;

	int font;				//ゲームフォント

};