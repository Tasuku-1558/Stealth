#include "Cake.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cakePosition">�P�[�L�̍��W</param>
Cake::Cake(const VECTOR& cakePosition)
	: alive(true)
	, RADIUS(50.0f)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
{
	position = cakePosition;

	Initialize();
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
	//�P�[�L���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE));

	//�P�[�L���f���̃T�C�Y�Ɖ�]�l�ƈʒu��ݒ�
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);
	MV1SetPosition(modelHandle, position);

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
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
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Cake::Update(float deltaTime)
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
/// �P�[�L�ɏՓ˂���
/// </summary>
void Cake::HitCake()
{
	alive = false;
}

/// <summary>
/// �`�揈��
/// </summary>
void Cake::Draw()
{
	MV1DrawModel(modelHandle);
}