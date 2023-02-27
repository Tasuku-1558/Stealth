#include "MonitoringEnemy.h"
#include "ModelManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Bullet.h"
#include "HitChecker.h"

using namespace Math3d;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pos"></param>
/// <param name="changeDir"></param>
/// <param name="currentDir"></param>
MonitoringEnemy::MonitoringEnemy(const VECTOR& pos, VECTOR changeDir, VECTOR currentDir)
	: EnemyBase()
	, dirCount(0.0f)
	, anotherDir()
	, initialDir()
	, IMAGE_FOLDER_PATH("data/image/")
	, MARK_PATH("mark.png")
{
	position = pos;
	anotherDir = changeDir;
	initialDir = currentDir;

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MonitoringEnemy::~MonitoringEnemy()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void MonitoringEnemy::Initialize()
{
	//���f���̓ǂݍ���
	modelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY));
	MV1SetDifColorScale(modelHandle, GetColorF(0.0f, 0.5f, 2.0f, 1.0f));

	visualModelHandle = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(ModelManager::ENEMY_VISUAL));

	//�摜�̓ǂݍ���
	markImage		= LoadGraph(InputPath(IMAGE_FOLDER_PATH, MARK_PATH).c_str());
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="imagePath"></param>
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
}

/// <summary>
/// �I������
/// </summary>
void MonitoringEnemy::Finalize()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(visualModelHandle);

	DeleteGraph(markImage);

	for (int i = 0; i < CAKE_IMAGE_NUMBER; i++)
	{
		DeleteGraph(cakeImage[i]);
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
/// <param name="hitChecker"></param>
void MonitoringEnemy::Update(float deltaTime, Player* player, HitChecker* hitChecker)
{
	//�x�N�g���̐��K��
	dir = VNorm(dir);

	DirMove(deltaTime);

	position += dir * deltaTime;

	//�G�l�~�[�̈ʒu�ƌ������Z�b�g
	MV1SetPosition(modelHandle, position);
	MV1SetRotationYUseDir(modelHandle, dir, 0.0f);

	//�G�l�~�[�̎��샂�f���̈ʒu�ƌ������Z�b�g
	MV1SetPosition(visualModelHandle, position);
	MV1SetRotationYUseDir(visualModelHandle, dir, 0.0f);


	VisualAnglePlayer(player);

	hitChecker->EnemyAndPlayer(player->GetPosition(), position);

	if (hitChecker->EnemyHit())
	{
		playerSpotted = true;
	}
}

/// <summary>
/// �G�l�~�[�̌����̏���
/// </summary>
/// <param name="deltaTime"></param>
void MonitoringEnemy::DirMove(float deltaTime)
{
	dirCount += deltaTime;

	//2�b�o�߂�����G�l�~�[�̌�����ύX����
	if (dirCount > 2.0f)
	{
		dir = anotherDir;
	}
	else
	{
		dir = initialDir;
	}

	//4�b�o�߂�����J�E���g��0�ɂ���
	if (dirCount > 4.0f)
	{
		dirCount = 0.0f;
	}
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
			//object = Object::PLAYER;

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
/// �G�l�~�[�̃v���C���[�̔���
/// </summary>
void MonitoringEnemy::Reaction()
{
	//switch (object)
	//{
	//case Object::PLAYER:

	//	//�v���C���[�𔭌�����
	//	playerSpotted = true;

	//	break;
	//}
}

/// <summary>
/// ���A�N�V�����摜�̕`�揈��
/// </summary>
void MonitoringEnemy::ReactionDraw()
{
	//�G�l�~�[�Ɍ���������
	if (playerSpotted)
	{
		//�r�b�N���}�[�N�̉摜��`��
		DrawBillboard3D(VGet(position.x - 300.0f, 0.0f, position.z - 100.0f), 0.5f, 0.5f, 200.0f, 0.0f, markImage, TRUE);
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