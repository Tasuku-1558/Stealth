#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="inEffect"></param>
Player::Player(EffectManager* const inEffect)
	: PlayerBase()
	, initialCount(0.0f)
	, pastPosition()
	, afterImageModelHandle()
	, IMAGE_FOLDER_PATH("Data/image/")
	, PLAYER_FIND_PATH("playerFind.png")
	, AFTER_IMAGE_NUMBER(12)
{
	effectManager = inEffect;

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	//�v���C���[���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//�c���̖������ǂݍ���
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		//�v���C���[�c�����f���̓ǂݍ���
		afterImageModelHandle[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

		//���f���̕s�����x�̐ݒ�
		//0.0f�ɋ߂��قǓ����x���オ��
		MV1SetOpacityRate(afterImageModelHandle[i], OPACITY);

		//���f���̃G�~�b�V�u�J���[��ύX
		MV1SetMaterialEmiColor(afterImageModelHandle[i], 0, AFTER_IMAGE_COLOR);
	}

	//�摜�̓ǂݍ���
	playerFindImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());
}

/// <summary>
/// �p�X�̓���
/// </summary>
/// <param name="folderPath">�摜�t�H���_�[�̃p�X</param>
/// <param name="path">�摜�̃p�X</param>
/// <returns></returns>
string Player::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DeleteModel(afterImageModelHandle[i]);
	}

	DeleteGraph(playerFindImage);
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	position = POSITION;
	nextPosition = POSITION;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		pastPosition[i] = POSITION;
	}

	direction = DIRECTION;
	speed = SPEED;

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Update(float deltaTime, VECTOR back, bool mapHit)
{
	Move(deltaTime, back, mapHit);

	AfterImage();

	//�����蔻�苅�̈ړ�����
	collisionSphere.Move(position);
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Move(float deltaTime, VECTOR back, bool mapHit)
{
	//���͕���������������
	inputDirection = ZERO_VECTOR;

	//�㉺�ړ�
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_W))
	{
		inputDirection += UP;
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += DOWN;
		inputFlag = true;
	}
	//���E�ړ�
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += RIGHT;
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += LEFT;
		inputFlag = true;
	}

	//�\���L�[�̓��͂���������
	if (inputFlag)
	{

		//���E�E�㉺���������Ȃǂœ��̓x�N�g����0�̎��͈ړ��ł��Ȃ�
		if (VSize(inputDirection) < 1.0f)
		{
			return;
		}

		//�\���L�[�̓��͕����𐳋K��
		direction = VNorm(inputDirection);
		
		//�\���L�[�̈ړ������Ɉړ�
		nextPosition += direction * speed * deltaTime;

		//�}�b�v�ɏՓ˂���
		HitMap(back, mapHit);
	}

	//���f���̈ʒu�ƌ�����ݒ�
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, direction, 0.0f);
}

/// <summary>
/// �}�b�v�ɏՓ˂���
/// </summary>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::HitMap(VECTOR back, bool mapHit)
{
	//�}�b�v�Ƀv���C���[���Փ˂����Ȃ��
	if (mapHit)
	{
		//�����̈ʒu�ɉ����߂��̒l��������
		nextPosition = back;

		position = nextPosition;
		nextPosition = position;
	}
	else
	{
		position = nextPosition;
		nextPosition = position;
	}
}

/// <summary>
/// �v���C���[�̎c������
/// </summary>
void Player::AfterImage()
{
	for (int i = AFTER_IMAGE_NUMBER - 1; i >= 1; i--)
	{
		pastPosition[i] = pastPosition[i - 1];
		MV1SetPosition(afterImageModelHandle[i], pastPosition[i] - AFTER_IMAGE_ADJUSTMENT);
		MV1SetRotationYUseDir(afterImageModelHandle[i], direction, 0.0f);
	}

	pastPosition[0] = position;
	MV1SetPosition(afterImageModelHandle[0], pastPosition[0] - AFTER_IMAGE_ADJUSTMENT);
	MV1SetRotationYUseDir(afterImageModelHandle[0], direction, 0.0f);
}

/// <summary>
/// �G�l�~�[�Ɍ��������ꍇ
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="spotted"></param>
void Player::FoundEnemy(float deltaTime, bool spotted)
{
	//�G�l�~�[�Ɍ���������
	if (spotted)
	{
		//�v���C���[�̓������~�߂�
		speed = 0.0f;

		//�G�l�~�[�Ɍ����������̉摜��\��
		findImageFlag = true;

		//�����ʒu�ɖ߂��J�E���g���J�n����
		initialCount += deltaTime;

		//��x�����T�E���h�𗬂�
		if (!spottedSeFlag)
		{
			//�G�l�~�[�Ɍ�����������SE�����Đ�
			SoundManager::GetInstance().SePlayFlag(SoundManager::ENEMY_FIND);

			spottedSeFlag = true;
		}

		FoundCount();
	}
}

/// <summary>
/// �G�l�~�[�Ɍ����������̏����ʒu�֖߂��J�E���g
/// </summary>
void Player::FoundCount()
{
	//�������J�E���g��0.8�b�o�߂�����
	if (initialCount > initialTime)
	{
		//�ʒu�ƌ����������ʒu��
		//�X�s�[�h�����ɖ߂�
		position = POSITION;
		nextPosition = POSITION;
		inputFlag = false;

		for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
		{
			pastPosition[i] = POSITION;
		}

		direction = DIRECTION;

		speed = SPEED;

		initialCount = 0.0f;

		//�G�l�~�[�Ɍ��������񐔂�1�v���X����
		playerFindCount++;

		findImageFlag = false;
		spottedSeFlag = false;

		//���X�|�[���G�t�F�N�g���o��
		effectManager->CreateRepopEffect(position);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	//�G�l�~�[�Ɍ��������Ȃ��
	if (findImageFlag)
	{
		//���������Ƃ����摜��`��
		DrawGraph(findImageX, findImageY, playerFindImage, TRUE);
	}

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(afterImageModelHandle[i]);
	}

	MV1DrawModel(modelHandle);
}