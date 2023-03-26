#pragma once

//シーンの種類
enum class SceneType
{
	TITLE,			//タイトル画面
	SELECTION,		//セレクション画面
	GAME,			//ゲーム画面
	RESULT,			//リザルト画面
	END,			//終了
};

/// <summary>
/// シーンベースクラス
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneType sceneType);
	virtual ~SceneBase();

	virtual void Initialize() = 0;					//初期化処理
	virtual SceneType Update(float deltaTime) = 0;	//更新処理
	virtual void Draw() = 0;						//描画処理

	SceneBase* CreateScene(SceneType nowScene);		//新しいシーンを生成する

	int Get() { return number; }
	
protected:

	SceneType nowSceneType;						//今のシーン

private:
	SceneBase(const SceneBase&);				//コピーコンストラクタ

	int number;
};