#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "KeyManager.h"

using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() : PlayerBase()
	, initialCount(0.0f)
	, pastPosition()
	, emptyModel()
	, SOUND_FOLDER_PATH("data/sound/")
	, IMAGE_FOLDER_PATH("data/image/")
	, PLAYER_FIND_PATH("playerFind.png")
	, SPOTTED_SE_PATH("spotted.mp3")
	, AFTER_IMAGE_NUMBER(12)
{
	//�����Ȃ�
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
	//�v���C���[���f��
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));

	//�v���C���[�c�����f��
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		emptyModel[i] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
		MV1SetOpacityRate(emptyModel[i], 0.05f);
		MV1SetMaterialEmiColor(emptyModel[i], 0, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
	}

	playerFindImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());

	spottedSe = LoadSoundMem(InputPath(SOUND_FOLDER_PATH, SPOTTED_SE_PATH).c_str());
}

/// <summary>
/// �p�X�̓���
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
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
		MV1DeleteModel(emptyModel[i]);
	}

	DeleteGraph(playerFindImage);

	//�T�E���h���\�[�X���폜
	InitSoundMem();
}

/// <summary>
/// ����������
/// </summary>
void Player::Activate()
{
	position = POSITION;
	previewPosition = POSITION;

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		pastPosition[i] = position;
	}

	dir = DIR;
	speed = SPEED;
	playerFindCount = 0;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Update(float deltaTime, Camera* camera, VECTOR back, bool mapHit)
{
	Move(deltaTime, camera, back, mapHit);

	AfterImage();
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="camera"></param>
/// <param name="back"></param>
/// <param name="mapHit"></param>
void Player::Move(float deltaTime, Camera* camera, VECTOR back, bool mapHit)
{
	inputDirection = ZERO_VECTOR;

	inputFlag = false;

	//�㉺
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_W))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_S))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;
	}
	//���E
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_D))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;
	}
	if (KeyManager::GetInstance().CheckPressed(KEY_INPUT_A))
	{
		inputDirection += camera->GetLeft();
		inputFlag = true;
	}

	//�\���L�[�̓��͂���������
	if (inputFlag)
	{

		// ���E�E�㉺���������Ȃǂœ��̓x�N�g����0�̎�
		if (VSquareSize(inputDirection) < 0.5f)
		{
			return;
		}

		//�\���L�[�̓��͕����𐳋K��
		inputDirection = VNorm(inputDirection);

		//�\���L�[�̓��͕������L�����̌����Ƃ���
		dir = inputDirection;
		
		//�\���L�[�̈ړ������Ɉړ�
		previewPosition += dir * speed * deltaTime;

		//�}�b�v�ɏՓ˂���
		HitMap(back, mapHit);
	}

	//���f���̈ʒu�ƌ�����ݒ�
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, dir, 0.0f);
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
		previewPosition = back;

		position = previewPosition;
		previewPosition = position;
	}
	else
	{
		position = previewPosition;
		previewPosition = position;
	}
}

/// <summary>
/// �v���C���[�̎c������
/// </summary>
void Player::AfterImage()
{
	for (int i = 11; i >= 1; i--)
	{
		pastPosition[i] = pastPosition[i - 1];
		MV1SetPosition(emptyModel[i], pastPosition[i] - VGet(0.0f, 10.0f, 0.0f));
	}

	pastPosition[0] = position;
	MV1SetPosition(emptyModel[0], pastPosition[0] - VGet(0.0f, 10.0f, 0.0f));

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1SetRotationYUseDir(emptyModel[i], dir, 0.0f);
	}
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
			PlaySoundMem(spottedSe, DX_PLAYTYPE_BACK);

			spottedSeFlag = true;
		}
	}

	//�J�E���g��0.6�b�o�߂�����
	if (initialCount > 0.6f)
	{
		//�ʒu�ƌ����������ʒu��
		//�X�s�[�h�����ɖ߂�
		position = POSITION;
		previewPosition = POSITION;

		for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
		{
			pastPosition[i] = position;
		}

		dir = DIR;
		speed = SPEED;

		playerFindCount++;
		initialCount = 0.0f;
		findImageFlag = false;
		spottedSeFlag = false;
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
		DrawGraph(50, -100, playerFindImage, TRUE);
	}

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(emptyModel[i]);
	}

	MV1DrawModel(modelHandle);
}