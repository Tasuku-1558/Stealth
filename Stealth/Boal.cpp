#include "Boal.h"
#include "ModelManager.h"


const VECTOR Boal::POSITION = { 2300.0f,0.0f,-540.0f };

Boal::Boal() : ObjectBase()
{
}

Boal::~Boal()
{
	// èIóπèàóùÇ™åƒÇŒÇÍÇƒÇ¢Ç»ÇØÇÍÇŒ
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Boal::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::BOAL));
}

void Boal::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Boal::Activate()
{
	position = POSITION;
}

void Boal::Update()
{
	MV1SetPosition(modelHandle, position);
}

void Boal::Draw()
{
	MV1DrawModel(modelHandle);
}