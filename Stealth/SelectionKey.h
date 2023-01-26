//#pragma once
//
//#include "SceneManager.h"
//
//
///// <summary>
///// ステージ切り替えクラス
///// </summary>
//class SelectionKey final
//{
//public:
//	SelectionKey(SceneManager* const sceneManager);
//	virtual ~SelectionKey();
//
//	void Initialize();								//初期化処理
//	void Finalize();								//終了処理
//	void Activate();								//活性化処理
//	void Draw();									//描画処理
//	void KeyMove();									//キー操作処理
//
//private:
//	SelectionKey(const SelectionKey&);				//コピーコンストラクタ
//
//	int StageCreator(int stageNumber);
//	int stageDecrement(int stageNumber);			//選択ステージを1個前に持っていく
//	int stageIncrement(int stageNumber);			//選択ステージを1個先に持っていく
//
//
//	int stageMax;									//最大ステージ数
//	int stageNo;									//ステージナンバー
//	bool changeScene;								//シーンを遷移させるか
//	int changeTimeCount;							//ステージ遷移カウント
//	int maxTime;									//マックスステージ遷移カウント
//
//
//};