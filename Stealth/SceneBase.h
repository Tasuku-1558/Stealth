#pragma once

//class SceneManager;

enum class SceneType
{
	TITLE,
	SELECTION,
	PLAY,
	RESULT,
	END
};

/// <summary>
/// SceneBaseクラス
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneType sceneType) : nowSceneType(sceneType) { /*処理なし*/ }
	virtual ~SceneBase(){/*処理なし*/}

	virtual void Initialize() = 0;				//初期化処理
	virtual void Finalize() = 0;				//終了処理
	virtual void Activate() = 0;				//活性化処理
	virtual SceneType Update(float deltaTime) = 0;	//更新処理
	virtual void Draw() = 0;					//描画処理

	
protected:

	SceneType nowSceneType; //今のSceneType


private:
	SceneBase(const SceneBase&);				//コピーコンストラクタ
};