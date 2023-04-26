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
	Entry(const Entry&);	//�R�s�[�R���X�g���N�^

	std::vector<Stage*> stage;

};