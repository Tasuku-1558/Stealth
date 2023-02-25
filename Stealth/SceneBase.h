#pragma once

class SceneManager;

/// <summary>
/// SceneBaseクラス
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneManager* const sceneManager) : parent(sceneManager){};
	virtual ~SceneBase(){};

	virtual void Initialize() = 0;				//初期化処理
	virtual void Finalize() = 0;				//終了処理
	virtual void Activate() = 0;				//活性化処理
	virtual void Update(float deltaTime) = 0;	//更新処理
	virtual void Draw() = 0;					//描画処理

protected:
	SceneManager* const parent;

	//シーンの状態
	//enum Scene
	//{
	//	TITLE,		//タイトル画面
	//	SELECTION,	//選択画面
	//	PLAY,		//ゲーム画面
	//	RESULT,		//リザルト画面
	//};

private:
	SceneBase(const SceneBase&);				//コピーコンストラクタ
};