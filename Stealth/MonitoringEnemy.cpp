#include "MonitoringEnemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Bullet.h"

const string MonitoringEnemy::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string MonitoringEnemy::SOUND_FOLDER_PATH = "data/sound/";		//sound�t�H���_�܂ł̃p�X
const string MonitoringEnemy::PLAYER_FIND_PATH = "playerFind.png";	//�v���C���[���������摜�̃p�X
const string MonitoringEnemy::MARK_PATH = "mark.png";			//�r�b�N���}�[�N�摜�̃p�X
const string MonitoringEnemy::CAKE_PATH = "ui9.png";			//�P�[�L�摜�̃p�X
const string MonitoringEnemy::CAKE_HALF_PATH = "cakeHalf.png";		//�P�[�L�������摜�̃p�X
const string MonitoringEnemy::SPOTTED_SE_PATH = "spotted.mp3";		//�v���C���[����SE���̃p�X


using namespace Math3d;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="id"></param>
MonitoringEnemy::MonitoringEnemy(std::vector<VECTOR>& id) : EnemyBase()
	, cakeCount(0.0f)
	, cakeFindFlag(false)
	, cakeEatFlag(false)
	, cakeHalfFlag(false)
{
	enemyState = EnemyState::CRAWL;
	Position(id);

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MonitoringEnemy::~MonitoringEnemy()
{
	//�I���������Ă΂�ĂȂ����
	if (modelHandle != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void MonitoringEnemy::Initialize()
{
	//���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));

	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//�ǂݍ��ݎ��s�ŃG���[
	if (modelHandle < 0 || visualModelHandle < 0)
	{
		printfDx("���f���f�[�^�ǂݍ��݂Ɏ��s\n");
	}

	dir = ZERO_VECTOR;

	//�摜�ǂݍ���
	playerFindImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, PLAYER_FIND_PATH).c_str());

	markImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());

	cakeImage[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_PATH).c_str());

	cakeImage[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, CAKE_HALF_PATH).c_str());

	spottedSE = LoadSoundMem(InputPath(SOUND_FOLDER_PATH, SPOTTED_SE_PATH).c_str());
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
std::string MonitoringEnemy::InputPath(string folderPath, string imagePath)
{
	return std::string(folderPath + imagePath);
}

/// <summary>
/// ����������
/// </summary>
void MonitoringEnemy::Activate()
{
	dir = ZERO_VECTOR;
	playerSpotted = false;
	cakeFlag = false;
	cakeFindFlag = false;
	cakeEatFlag = false;
	cakeHalfFlag = false;
	cakeCount = 0.0f;
}

/// <summary>
/// �G�l�~�[�ʒu�ݒ�
/// </summary>
/// <param name="id"></param>
void MonitoringEnemy::Position(std::vector<VECTOR>& id)
{
	pointList = id;					//�}�b�v������W���X�g���󂯎��

	itr = pointList.begin();		//�C�e���[�^��擪�ɐݒ�

	dir = *itr++;				//�C�e���[�^����G���W��ݒ�

	enemyState = EnemyState::ARRIVAL;
}

/// <summary>
/// �I������
/// </summary>
void MonitoringEnemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(visualModelHandle);

	DeleteGraph(playerFindImage);
	DeleteGraph(markImage);

	for (int i = 0; i < CAKE_IMAGE_NUMBER; i++)
	{
		DeleteGraph(cakeImage[i]);
	}

	//�T�E���h���\�[�X���폜
	InitSoundMem();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void MonitoringEnemy::Update(float deltaTime, Player* player)
{
	//�x�N�g���̐��K��
	dir = VNorm(targetPosition - dir);

	position += dir * speed * deltaTime;

	//�G�l�~�[�̈ʒu���Z�b�g
	MV1SetPosition(modelHandle, position);

	//�G�l�~�[�̎��샂�f�����Z�b�g
	MV1SetPosition(visualModelHandle, position);

	VisualAnglePlayer(player);

	eUpdate(deltaTime);

	//z�����t�������Ă���̂�dir��180�x��]������
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);

	//���f���ɉ�]���Z�b�g
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	MV1SetRotationZYAxis(visualModelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

/// <summary>
/// �ړI�n�܂ňړ�����
/// </summary>
void MonitoringEnemy::SetTargetPosition()
{
	targetPosition = *itr++;

	//�ŏI�ړI�n�ɓ��������玟�̖ړI�n�������ʒu�ɂ���
	if (itr == pointList.end())
	{
		itr = pointList.begin();
	}

	enemyState = EnemyState::CRAWL;
}

/// <summary>
/// �ړI�n�ɓ��B�����Ȃ��
/// </summary>
/// <param name="deltaTime"></param>
/// <returns></returns>
bool MonitoringEnemy::IsGoal(float deltaTime)
{
	return VSize(targetPosition - dir) < speed * deltaTime;
}

/// <summary>
/// �G�l�~�[�̎���Ƀv���C���[���������ꍇ
/// </summary>
/// <param name="player"></param>
void MonitoringEnemy::VisualAnglePlayer(Player* player)
{
	//�v���C���[����G�l�~�[�̍��W���������l���擾
	VECTOR sub = player->GetPosition() - position;

	//�v���C���[�ƃG�l�~�[��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);

	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > direction)
	{
		//�v���C���[���G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			object = Object::PLAYER;

			//����͈͓��Ȃ��
			Reaction();
		}
	}
	else
	{
		playerSpotted = false;
	}
}

/// <summary>
/// �G�l�~�[�̎���ɃP�[�L���������ꍇ
/// </summary>
/// <param name="bullet"></param>
/// <param name="deltaTime"></param>
void MonitoringEnemy::VisualAngleCake(Bullet* bullet, float deltaTime)
{
	//�o���b�g����G�l�~�[�̍��W���������l���擾
	VECTOR sub = bullet->GetPosition() - position;

	//�o���b�g�ƃG�l�~�[��2�_�Ԃ̋������v�Z
	bulletDirection = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);

	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > bulletDirection)
	{
		//�o���b�g���G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			object = Object::CAKE;

			//����͈͓��Ȃ��
			Reaction();

			CakeEatCount(deltaTime);
		}
	}
	else
	{
		//�G�l�~�[�̎���͈͊O�Ȃ�X�s�[�h�����̃X�s�[�h�ɖ߂�
		speed = SPEED;

		cakeFlag = false;

		cakeHalfFlag = false;

		//�J�E���g�̏�����
		cakeCount = 0.0f;
	}
}

/// <summary>
/// �b���ɂ���ăP�[�L�̏�ԕω�
/// </summary>
/// <param name="deltaTime"></param>
void MonitoringEnemy::CakeEatCount(float deltaTime)
{
	cakeCount += deltaTime;

	//�P�[�L�������ăJ�E���g��1.5�b�o�߂�����
	if (cakeCount > 1.5f)
	{
		speed = SPEED;

		//�r�b�N���}�[�N�摜���\���ɂ���
		cakeFindFlag = false;
	}

	//�P�[�L�������ăG�l�~�[�����̈ʒu�܂ňړ�������
	//�P�[�L�̉摜��\������
	if (270.0f > bulletDirection)
	{
		speed = 0.0f;
		cakeEatFlag = true;

		//�J�E���g��4�b�o�߂�����
		//�����ɂȂ����P�[�L�̉摜��\������
		if (cakeCount > 4.0f)
		{
			cakeEatFlag = false;

			cakeHalfFlag = true;
		}
	}
}

/// <summary>
/// �G�l�~�[�̎���ɕǂ��������ꍇ
/// </summary>
/// <param name="wallPos"></param>
void MonitoringEnemy::VisualAngleWall(VECTOR wallPos)
{
	//�ǂ���G�l�~�[�̍��W���������l���擾
	VECTOR sub = wallPos - position;

	//�ǂƃG�l�~�[��2�_�Ԃ̋������v�Z
	float direction = sqrt(pow(sub.x, 2) + pow(sub.z, 2));

	//�x�N�g���̐��K��
	sub = VNorm(sub);

	//���όv�Z
	float dot = VDot(sub, dir);

	float range = RANGE_DEGREE * (float)(DX_PI / 180.0f);

	//�G�l�~�[�̎����cos�ɂ���
	float radian = cosf(range / 2.0f);

	//�x�N�g���ƃG�l�~�[�̒����̔�r
	if (length > direction)
	{
		//�ǂ��G�l�~�[�̎���͈͓��ɂ���Ȃ��
		if (radian <= dot)
		{
			object = Object::WALL;

			//����͈͓��Ȃ��
			Reaction();
		}
	}
}

/// <summary>
/// �G�l�~�[�̃I�u�W�F�N�g���Ƃ̔���
/// </summary>
void MonitoringEnemy::Reaction()
{
	switch (object)
	{
	case Object::PLAYER:

		//�v���C���[�𔭌�����
		playerSpotted = true;

		break;

	case Object::CAKE:

		cakeFlag = true;

		//�P�[�L��������
		cakeFindFlag = true;

		//�G�l�~�[�̓������~�߂�
		speed = 0.0f;

		break;

	case Object::WALL:
		break;
	}
}

/// <summary>
/// �G�l�~�[�̏��
/// </summary>
/// <param name="deltaTime"></param>
void MonitoringEnemy::eUpdate(float deltaTime)
{
	switch (enemyState)
	{
	case EnemyState::CRAWL:

		if (IsGoal(deltaTime))
		{
			enemyState = EnemyState::ARRIVAL;
		}

		break;

	case EnemyState::ARRIVAL:
		SetTargetPosition();
		break;
	}
}

/// <summary>
/// ���A�N�V�����摜�̕`�揈��
/// </summary>
void MonitoringEnemy::ReactionDraw()
{
	//�G�l�~�[�Ɍ���������
	if (playerSpotted)
	{
		//�G�l�~�[�̓������~�߂�
		speed = 0.0f;

		//�r�b�N���}�[�N�̉摜��`��
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);

		//�G�Ɍ��������Ƃ���UI�摜��`��
		DrawGraph(50, -100, playerFindImage, TRUE);

		// ����SE���Đ�
		//PlaySoundMem(spottedSE, DX_PLAYTYPE_BACK);
	}

	//�P�[�L���������Ȃ��
	if (cakeFindFlag)
	{
		//�r�b�N���}�[�N�摜��`��
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
	}

	//�P�[�L�ɃG�l�~�[���߂Â����Ȃ��
	if (cakeEatFlag)
	{
		//�P�[�L�̉摜��`��
		DrawBillboard3D(VGet(position.x + 100.0f, 800.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[0], TRUE);
	}

	//�P�[�L���G�l�~�[�ɋ߂Â���4�b�o�߂�����
	if (cakeHalfFlag)
	{
		//�P�[�L�������̉摜��`��
		DrawBillboard3D(VGet(position.x + 100.0f, 800.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, cakeImage[1], TRUE);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void MonitoringEnemy::Draw()
{
	ReactionDraw();

	MV1DrawModel(modelHandle);

	MV1DrawModel(visualModelHandle);
}