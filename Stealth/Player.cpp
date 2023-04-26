#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "InputManager.h"

using namespace Math3d;		//VECTOR�̌v�Z�Ɏg�p

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="inEffect">�G�t�F�N�g�}�l�[�W���[�̃|�C���^</param>
/// <param name="inMapHit">�}�b�v�ƏՓ˂������ǂ���</param>
/// <param name="inPushBack">�v���C���[�ւ̉����߂���</param>
Player::Player(EffectManager* const inEffect, bool inMapHit, VECTOR inPushBack)
{
	effectManager = inEffect;

	mapHit = inMapHit;

	pushBack = inPushBack;

	Initialize();
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

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		//�v���C���[�c�����f���̓ǂݍ���
		afterImageModel[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

		//���f���̕s�����x�̐ݒ�
		//0.0f�ɋ߂��قǓ����x���オ��
		MV1SetOpacityRate(afterImageModel[i], OPACITY);

		//���f���̃G�~�b�V�u�J���[��ύX
		MV1SetMaterialEmiColor(afterImageModel[i], MATERIAL_INDEX, AFTER_IMAGE_COLOR);

		pastPosition[i] = POSITION;
	}

	//���������摜�̓ǂݍ���
	playerFindImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());

	position = POSITION;
	nextPosition = POSITION;

	direction = DIRECTION;
	speed = SPEED;

	//�����蔻�苅�̏��ݒ�
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = POSITION;
	collisionSphere.radius = RADIUS;
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DeleteModel(afterImageModel[i]);
	}

	DeleteGraph(playerFindImage);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Player::Update(float deltaTime)
{
	Move(deltaTime);

	AfterImage();
}

/// <summary>
/// �L�[���͏���
/// </summary>
void Player::KeyInput()
{
	Key key[] =
	{
		{KEY_INPUT_W, UP},
		{KEY_INPUT_S, DOWN},
		{KEY_INPUT_D, RIGHT},
		{KEY_INPUT_A, LEFT},
	};

	for (int i = 0; i < KEY_INPUT_PATTERN; i++)
	{
		if (KeyManager::GetInstance().CheckPressed(key[i].input))
		{
			inputDirection += key[i].dir;
			inputFlag = true;
		}
	}
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void Player::Move(float deltaTime)
{
	//���͕���������������
	inputDirection = ZERO_VECTOR;

	KeyInput();

	//�L�[�̓��͂���������
	if (inputFlag)
	{
		//���E�E�㉺���������Ȃǂœ��̓x�N�g����0�̎��͈ړ��ł��Ȃ�
		if (VSize(inputDirection) < MAX_INPUT_DIRECTION)
		{
			return;
		}

		//�L�[�̓��͕����𐳋K��
		direction = VNorm(inputDirection);
		
		//�L�[�̈ړ������Ɉړ�
		nextPosition += direction * speed * deltaTime;

		HitMap();
	}

	//���f���̈ʒu�ƌ�����ݒ�
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, direction, Y_ANGLE);

	//�����蔻�苅�̈ړ�����
	collisionSphere.Move(position);
}

/// <summary>
/// �}�b�v�ɏՓ˂������ǂ���
/// </summary>
void Player::HitMap()
{
	//�}�b�v�Ƀv���C���[���Փ˂����Ȃ��
	if (mapHit)
	{
		//�����̈ʒu�ɉ����߂��̒l��������
		nextPosition = pushBack;

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
		MV1SetPosition(afterImageModel[i], pastPosition[i] - AFTER_IMAGE_ADJUSTMENT);
		MV1SetRotationYUseDir(afterImageModel[i], direction, Y_ANGLE);

		pastPosition[0] = position;
		MV1SetPosition(afterImageModel[0], pastPosition[0] - AFTER_IMAGE_ADJUSTMENT);
		MV1SetRotationYUseDir(afterImageModel[0], direction, Y_ANGLE);
	}
}

/// <summary>
/// �G�l�~�[�Ɍ��������ꍇ
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
/// <param name="spotted">�G�l�~�[�Ɍ����������ǂ���</param>
void Player::FoundEnemy(float deltaTime, bool spotted)
{
	//�G�l�~�[�Ɍ���������
	if (spotted)
	{
		//�v���C���[�̓������~�߂�
		speed = STOP_SPEED;

		//�G�l�~�[�Ɍ����������̉摜��\��
		findImageFlag = true;

		//�����ʒu�ɖ߂��J�E���g���J�n����
		initialTime += deltaTime;

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
	if (initialTime > MAX_INITIAL_TIME)
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

		initialTime = INITIAL_TIME;

		//�G�l�~�[�Ɍ��������񐔂�1�v���X����
		playerFindCount++;

		findImageFlag = false;
		spottedSeFlag = false;

		//���X�|�[���G�t�F�N�g���o��
		effectManager->CreateEffect(position, EffectManager::RESPAWN);
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
		DrawGraph(FIND_IMAGE_X, FIND_IMAGE_Y, playerFindImage, TRUE);
	}

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(afterImageModel[i]);
	}

	MV1DrawModel(modelHandle);
}