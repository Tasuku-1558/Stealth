#include "Entry.h"
#include "Stage.h"


Entry::Entry()
{
}

Entry::~Entry()
{
}

void Entry::EntryStage(Stage* newStage)
{
	stage.emplace_back(newStage);
}