#include "Cake.h"
#include "ModelManager.h"
#include "HitChecker.h"


//const VECTOR Cake::SIZE	= { 20.0f, 20.0f, 20.0f };		//���f���̔{��


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
Cake::Cake(const VECTOR& pos) : ObjectBase()
	, alive(true)
	, SIZE({ 20.0f, 20.0f, 20.0f })
{
	position = pos;
	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Cake::~Cake()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Cake::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE));
	MV1SetScale(modelHandle, SIZE);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// ����������
/// </summary>
void Cake::Activate()
{
	CakeAlive();
}

/// <summary>
/// �I������
/// </summary>
void Cake::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �X�V����
/// </summary>
void Cake::Update()
{
	//�����Ȃ�
}

/// <summary>
/// �P�[�L���A�N�e�B�u��
/// </summary>
void Cake::CakeAlive()
{
	alive = true;
	position = position;
}

/// <summary>
/// �P�[�L�������Ă邩����ł��邩�𔻒�
/// </summary>
/// <param name="hitChecker"></param>
void Cake::IsAlive(HitChecker* hitChecker)
{
	//�P�[�L�ɓ��������Ȃ��
	if (hitChecker->CakeHit())
	{
		alive = false;
	}
	else
	{
		alive = true;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Cake::Draw()
{
	MV1DrawModel(modelHandle);
}