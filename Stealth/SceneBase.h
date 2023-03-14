#pragma once

//シーンの種類
enum class SceneType
{
	TITLE,			//タイトル画面
	SELECTION,		//セレクション画面
	PLAY,			//ゲーム画面
	RESULT,			//リザルト画面
	END,			//終了
};

/// <summary>
/// SceneBaseクラス
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneType sceneType) : nowSceneType(sceneType) { /*処理なし*/ }
	virtual ~SceneBase(){/*処理なし*/}

	virtual void Initialize() = 0;					//初期化処理
	virtual void Finalize() = 0;					//終了処理
	virtual void Activate() = 0;					//活性化処理
	virtual SceneType Update(float deltaTime) = 0;	//更新処理
	virtual void Draw() = 0;						//描画処理

	
protected:

	SceneType nowSceneType;						//今のシーン


private:
	SceneBase(const SceneBase&);				//コピーコンストラクタ
};