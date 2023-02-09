#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"


const string Player::SOUND_FOLDER_PATH  = "data/sound/";		//sound�t�H���_�܂ł̃p�X
const string Player::SPOTTED_SE_PATH    = "spotted.mp3";		//�G�l�~�[�Ɍ�����������SE���̃p�X
const int	 Player::AFTER_IMAGE_NUMBER = 3;					//�v���C���[�̎c������

using namespace Math3d;
using namespace std;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() : PlayerBase()
	, initialCount(0.0f)
	, pastPosition()
	, emptyModel()
	, count(0.0f)
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
		MV1SetOpacityRate(emptyModel[i], 0.3f);
		MV1SetMaterialEmiColor(emptyModel[i], 0, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));
	}

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s[PLAYER]\n");
	}

	//SE���̓ǂݍ���
	string failePath = SOUND_FOLDER_PATH + SPOTTED_SE_PATH;
	spottedSe = LoadSoundMem(failePath.c_str());
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	MV1DeleteModel(modelHandle);

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
		pastPosition[i] = POSITION;
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

	MV1SetPosition(modelHandle, position);

	AfterImage(deltaTime);
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
	if (CheckHitKey(KEY_INPUT_W))
	{
		inputDirection += camera->GetUp();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		inputDirection += camera->GetDown();
		inputFlag = true;
	}
	//���E
	if (CheckHitKey(KEY_INPUT_D))
	{
		inputDirection += camera->GetRight();
		inputFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_A))
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

	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g dir������
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1SetRotationZYAxis(emptyModel[i], negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	}

}

/// <summary>
/// �v���C���[�̎c��
/// </summary>
/// <param name="deltaTime"></param>
void Player::AfterImage(float deltaTime)
{
	count += deltaTime;

	if (count > 0.1f)
	{
		pastPosition[0] = position;

		MV1SetPosition(emptyModel[0], pastPosition[0]);

		if (count > 0.2f)
		{
			pastPosition[1] = pastPosition[0];

			MV1SetPosition(emptyModel[1], pastPosition[1]);

			if (count > 0.3f)
			{
				pastPosition[2] = pastPosition[1];

				MV1SetPosition(emptyModel[2], pastPosition[2]);

				count = 0.0f;
			}
		}
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
		//�����ʒu�ɖ߂��J�E���g���J�n����
		initialCount += deltaTime;

		//�v���C���[�̓������~�߂�
		speed = 0.0f;

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
		dir = DIR;
		speed = SPEED;

		playerFindCount++;
		initialCount = 0.0f;
		spottedSeFlag = false;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	for (int i = 0; i < AFTER_IMAGE_NUMBER; i++)
	{
		MV1DrawModel(emptyModel[i]);
	}

	MV1DrawModel(modelHandle);
}