#pragma once
#include <vector>
#include "PreCompiledHeader.h"

class Stage;

/// <summary>
/// ステージ生成クラス
/// </summary>
class StageCreator final
{
public:
	StageCreator();
	virtual ~StageCreator();

	void Draw();		//描画処理

private:
	StageCreator(const StageCreator&);		//コピーコンストラクタ

	void EntryStage(Stage* newStage);		//ステージを登録
	void DeleteStage(Stage* deleteStage);	//ステージを削除
	void StagePop(char stageNumber[BLOCK_NUM_Z][BLOCK_NUM_X]);		//ステージの出現

	std::vector<Stage*> stage;

	//定数
	const float STAGE_POS_Y;	//ステージのY座標
};