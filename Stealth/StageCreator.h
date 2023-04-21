#pragma once
#include <vector>

class Stage;

/// <summary>
/// ステージ生成クラス
/// </summary>
class StageCreator final
{
public:
	StageCreator();
	virtual ~StageCreator();

	void Draw();

private:
	StageCreator(const StageCreator&);		//コピーコンストラクタ

	void EntryStage(Stage* newStage);		//ステージを登録
	void DeleteStage(Stage* deleteStage);	//ステージを削除
	void StagePop();						//ステージの出現


	std::vector<Stage*> stage;

};