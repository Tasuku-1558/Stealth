#include "Player.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "Enemy.h"

const string Player::SOUND_FOLDER_PATH = "data/sound/";		//sound�t�H���_�܂ł̃p�X
const string Player::SPOTTED_SE_PATH   = "spotted.mp3";		//�G�l�~�[�Ɍ�����������SE���̃p�X

using namespace Math3d;
using namespace std;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player() : PlayerBase()
	, initialCount(0.0f)
	, pastPosition()
	, emptyModel(0)
	, count(0.0f)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	//�I���������Ă΂�Ă��Ȃ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
	emptyModel= MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::PLAYER));
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
	modelHandle = NULL;

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

	count += deltaTime;


	if (count > 1.0f)
	{
		pastPosition = position;

		MV1SetPosition(emptyModel, pastPosition);

		MV1SetMaterialEmiColor(emptyModel, 0, GetColorF(0.0f, 0.0f, 1.0f, 1.0f));

		count = 0.0f;
	}
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
}

/// <summary>
/// �G�l�~�[�Ɍ��������ꍇ
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="enemy"></param>
void Player::FoundEnemy(float deltaTime, Enemy* enemy)
{
	//�G�l�~�[�Ɍ���������
	if (enemy->Spotted())
	{
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
	MV1DrawModel(modelHandle);

	MV1DrawModel(emptyModel);
}