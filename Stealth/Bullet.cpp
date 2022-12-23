#include "Bullet.h"
#include "ModelManager.h"
#include "Boal.h"


const VECTOR Bullet::SIZE  = { 2.0f, 2.0f, 2.0f };		//���f���̔{��
const float  Bullet::SPEED = 800.0f;						//���f���̃X�s�[�h


using namespace Math3d;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	// �I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

void Bullet::Initialize()
{
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::BOAL);
	MV1SetScale(modelHandle, SIZE);


	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s [BOAL]\n");
	}
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

void Bullet::Activate(VECTOR inPosition, VECTOR inDir)
{
	position = inPosition;
	dir = inDir;
	
}

void Bullet::Update(float deltaTime, Boal* boal)
{
	if (!boal->GetAlive())
	{
		OnShot(deltaTime);
	}
	else
	{
		return;
	}
	
}

/// <summary>
/// ���������ꂽ��
/// </summary>
void Bullet::OnShot(float deltaTime)
{
	position += dir * deltaTime * SPEED;

	MV1SetPosition(modelHandle, position);
	
}

void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
}