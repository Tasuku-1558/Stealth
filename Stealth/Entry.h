#pragma once

#include <vector>

class Stage;
class CakeBullet;

class Entry final
{
public:
	Entry();
	virtual ~Entry();

	void EntryStage(Stage* newStage);

private:
	Entry(const Entry&);	//コピーコンストラクタ

	std::vector<Stage*> stage;

};