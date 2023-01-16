#pragma once

class SceneBase;

/// <summary>
/// シーンマネージャークラス
/// </summary>
class SceneManager final
{
public:

	 SceneManager();
	~SceneManager();

	void Initialize();
	void Finalize();
	void Update(float deltaTime);
	void Draw();

	//シーンの状態
	enum Scene
	{
		TITLE,			//タイトル画面
		SELECTION,		//ステージ選択画面
		STAGE1,			//ステージ1画面
		STAGE2,			//ステージ2画面
		//OVER,			//ゲームオーバー画面
		END				//終了とシーン数
	};

	void  SetNextScene(Scene next);		//次のシーンをセット
	Scene GetNowScene();				//今のシーンを取得
	Scene GetNextScene();				//次のシーンを取得

private:

	SceneManager(const SceneManager&);	//コピーコンストラクタ

	SceneBase* eachScene[Scene::END];	//各シーンのインスタンス
	SceneBase* nowPointer;				//今のシーンポインタ
	Scene	   nowScene;				//今のシーン
	Scene	   nextScene;				//次のシーン

	void ChangeScene();					//シーンの変更
};