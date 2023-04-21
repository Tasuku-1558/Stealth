#pragma once

#include "SceneBase.h"

class Camera;
class SelectionUi;
class FadeManager;


/// <summary>
/// ステージ選択画面クラス
/// </summary>
class StageSelection final : public SceneBase
{
public:
	StageSelection();
	virtual ~StageSelection();

	SceneType Update(float deltaTime)override;		//更新処理
	void Draw()override;							//描画処理

private:
	StageSelection(const StageSelection&);			//コピーコンストラクタ

	void Initialize()override;						//初期化処理
	void KeyMove(float deltaTime);					//キー操作
	int stageIncrement(int stageNumber);			//選択ステージを1つ先に持っていく
	int stageDecrement(int stageNumber);			//選択ステージを1つ前に持っていく
	int StageCreator(int stageNumber);				//各シーンへ遷移

	Camera* camera;
	SelectionUi* selectionUi;
	FadeManager* fadeManager;

	struct Stage
	{
		int number;				//ステージ番号
		SceneType sceneType;	//シーンの種類
	};

	int fontHandle;							//ゲームフォント
	int stageNo;							//ステージ番号
	int changeTimeCount;					//文字点滅カウント
	float frame;							//フレーム数
	float pushCount;						//ステージ切り替えカウント
	bool changeScene;						//シーンを切り替える
	

	//定数
	const int   MAX_STAGE;					//最大ステージ数
	const int	FIRST_STAGE_NUMBER;			//ステージ1の番号
	const int	SECOND_STAGE_NUMBER;		//ステージ2の番号
	const int	TITLE_RETURN_NUMBER;		//タイトルへ戻る番号
	const int   ADD_STAGE_NUMBER;			//ステージを切り替える数
	const int	SELECTION_FONT_SIZE;		//ゲームフォントのサイズ
	const int	FONT_THICK;					//フォントの太さ
	const float MAX_PUSH_COUNT;				//最大切り替えカウント
	const float PUSH_INTERVAL;				//切り替えカウントのインターバル
	const float FADE_START_FRAME;			//フェード開始フレーム

};