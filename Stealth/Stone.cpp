#include "Stone.h"
#include "ModelManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stonePosition"></param>
Stone::Stone(const VECTOR& stonePosition)
	: alive(true)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, RADIUS(50.0f)
{
	position = stonePosition;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stone::~Stone()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Stone::Initialize()
{
	//���΂̃��f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::STONE));

	//���f���̃T�C�Y,��]�l,�ʒu��ݒ�
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// ����������
/// </summary>
void Stone::Activate()
{
	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// �I������
/// </summary>
void Stone::Finalize()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �X�V����
/// </summary>
void Stone::Update(float deltaTime)
{
	//�����蔻�苅�̈ړ�����
	collisionSphere.Move(position);
}

/// <summary>
/// ���΂��A�N�e�B�u��
/// </summary>
void Stone::StoneAlive()
{
	alive = true;
	position = position;
}

/// <summary>
/// �`�揈��
/// </summary>
void Stone::Draw()
{
	MV1DrawModel(modelHandle);
}