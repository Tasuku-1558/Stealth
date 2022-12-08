#include "Field.h"
#include "ModelManager.h"


const VECTOR Field::POSITION = { 500.0f,0.0f,100.0f };

Field::Field() : ObjectBase()
{
}

Field::~Field()
{
	// èIóπèàóùÇ™åƒÇŒÇÍÇƒÇ¢Ç»ÇØÇÍÇŒ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Field::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BLOCK));
}

void Field::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Field::Activate()
{
	position = POSITION;
}

void Field::Update()
{
	MV1SetPosition(modelHandle, position);
}

void Field::Draw()
{
	MV1DrawModel(modelHandle);
}