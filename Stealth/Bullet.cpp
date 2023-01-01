#include "Bullet.h"
#include "ModelManager.h"
#include "Boal.h"


const VECTOR Bullet::SIZE  = { 2.0f, 2.0f, 2.0f };			//���f���̔{��
const float  Bullet::SPEED = 800.0f;						//���f���̃X�s�[�h
const string Bullet::IMAGE_FOLDER_PATH = "data/image/";     //image�t�H���_�܂ł̃p�X
const string Bullet::CURSOR_PATH	   = "pointer.png";		//�J�[�\���摜�̃p�X


using namespace Math3d;

Bullet::Bullet(Object BOAL)
	: cursorImage(0)
	, mouseX(-50)
	, mouseY(0)
{
	//�����Ȃ�
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

	string failePath = IMAGE_FOLDER_PATH + CURSOR_PATH;
	cursorImage = LoadGraph(failePath.c_str());
}

void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	DeleteGraph(cursorImage);
}

void Bullet::Activate()
{
	
	position = VGet(0.0f, 0.0f, 0.0f);
}

void Bullet::Update(float deltaTime, Boal* boal)
{
	if (!boal->GetAlive())
	{
		OnShot(deltaTime);
		//MouseMove(boal);
	}
	
}

/// <summary>
/// �}�E�X�J�[�\���̈ړ�
/// </summary>
/// <param name="boal"></param>
void Bullet::MouseMove(Boal* boal)
{
	if (!boal->GetAlive())
	{
		GetMousePoint(&mouseX, &mouseY);                //�}�E�X�̍��W�擾
	}
}

/// <summary>
/// ���������ꂽ��
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::OnShot(float deltaTime)
{
	
	position += VGet(mouseY-2700, 0.0f, mouseX-500);

	MV1SetPosition(modelHandle, position);
}

void Bullet::Draw()
{
	MV1DrawModel(modelHandle);

	DrawRotaGraph(mouseX, mouseY, 0.04f, 0, cursorImage, TRUE);
}