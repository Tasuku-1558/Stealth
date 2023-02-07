#include "ThirdStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "MonitoringEnemy.h"
#include "BallBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "ThirdStageMap.h"
#include "UiManager.h"


const float ThirdStage::GOAL_POSITION_X = -1900.0f;		//�S�[���̈ʒuX���W
const float ThirdStage::GOAL_POSITION_Z = 4600.0f;		//�S�[���̈ʒuZ���W
const int   ThirdStage::PARTICLE_NUMBER = 500;			//�p�[�e�B�N���̐�

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
ThirdStage::ThirdStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, light(nullptr)
	, camera(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy()
	, monitoringEnemy(nullptr)
	, pUpdate(nullptr)
	, ballBullet()
	, hitChecker(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, thirdStageMap(nullptr)
	, uiManager(nullptr)
	, font(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ThirdStage::~ThirdStage()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void ThirdStage::Initialize()
{
	//���C�g�N���X
	light = new Light();

	//�J�����N���X
	camera = new Camera();
	camera->Initialize();

	//�w�i�N���X
	backGround = new BackGround();
	backGround->Initialize();

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

	//�T�[�h�X�e�[�W�}�b�v�N���X
	thirdStageMap = new ThirdStageMap();
	thirdStageMap->Initialize();

	monitoringEnemy = new MonitoringEnemy(thirdStageMap->GetMap2());
	monitoringEnemy->Initialize();

	//�P�[�L�̍ďo���G�t�F�N�g�N���X
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//�o���֐�
	BallBulletPop();

	EnemyPop();
}

/// <summary>
/// �I������
/// </summary>
void ThirdStage::Finalize()
{
	SafeDelete(light);

	SafeDelete(camera);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(thirdStageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
	}

	for (auto ballBulletPtr : ballBullet)
	{
		SafeDelete(ballBulletPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
	}

	SafeDelete(uiManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void ThirdStage::Activate()
{
	state = State::START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &ThirdStage::UpdateStart;

	player->Activate();

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Activate();
	}

	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Activate();
	}

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	cakeEffect->Activate();

	uiManager->Activate();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}
}

/// <summary>
/// �G�l�~�[��o�^
/// </summary>
/// <param name="newEnemy"></param>
void ThirdStage::EntryEnemy(Enemy* newEnemy)
{
	enemy.emplace_back(newEnemy);
}

/// <summary>
/// �G�l�~�[���폜
/// </summary>
/// <param name="deleteEnemy"></param>
void ThirdStage::DeleteEnemy(Enemy* deleteEnemy)
{
	//�G�l�~�[�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(enemy.begin(), enemy.end(), deleteEnemy);

	if (iter != enemy.end())
	{
		//�G�l�~�[�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, enemy.end() - 1);
		enemy.pop_back();

		return;
	}
}

/// <summary>
/// �G�l�~�[�̏o��
/// </summary>
void ThirdStage::EnemyPop()
{
	Enemy* newEnemy = new Enemy(thirdStageMap->GetMap());
	EntryEnemy(newEnemy);

	Enemy* newEnemy2 = new Enemy(thirdStageMap->GetMap2());
	EntryEnemy(newEnemy2);
}

/// <summary>
/// �{�[���o���b�g��o�^
/// </summary>
/// <param name="newBallBullet"></param>
void ThirdStage::EntryBallBullet(BallBullet* newBallBullet)
{
	ballBullet.emplace_back(newBallBullet);
}

/// <summary>
/// �{�[���o���b�g���폜
/// </summary>
/// <param name="deleteBallBullet"></param>
void ThirdStage::DeleteBallBullet(BallBullet* deleteBallBullet)
{
	//�{�[���o���b�g�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(ballBullet.begin(), ballBullet.end(), deleteBallBullet);

	if (iter != ballBullet.end())
	{
		//�{�[���o���b�g�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, ballBullet.end() - 1);
		ballBullet.pop_back();

		return;
	}
}

/// <summary>
/// �{�[���o���b�g�̏o��
/// </summary>
void ThirdStage::BallBulletPop()
{
	BallBullet* newBallBullet = new BallBullet({ -600.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet);

	BallBullet* newBallBullet2 = new BallBullet({ -1400.0f,30.0f,2000.0f });
	EntryBallBullet(newBallBullet2);

	BallBullet* newBallBullet3 = new BallBullet({ -4000.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet3);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N����o�^
/// </summary>
/// <param name="newCakeParticle"></param>
void ThirdStage::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteCakeParticle"></param>
void ThirdStage::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
{
	//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(cakeParticle.begin(), cakeParticle.end(), deleteCakeParticle);

	if (iter != cakeParticle.end())
	{
		//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, cakeParticle.end() - 1);
		cakeParticle.pop_back();

		return;
	}
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N���̏o��
/// </summary>
void ThirdStage::CakeParticlePop()
{
	for (auto ballBulletPtr : ballBullet)
	{
		//�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u���p�[�e�B�N�����o�Ă��Ȃ��Ȃ��
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && ballBulletPtr->bullet->GetAlive() && !ballBulletPtr->cake->GetAlive() && !particleFlag)
		{
			//�p�[�e�B�N���̌����G���g���[����
			for (int i = 0; i < PARTICLE_NUMBER; i++)
			{
				CakeParticle* newCakeParticle = new CakeParticle(ballBulletPtr->bullet->GetPosition());
				EntryCakeParticle(newCakeParticle);
			}

			particleFlag = true;
		}
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateStart(float deltaTime)
{
	camera->Update(player->GetPosition());

	//�T�[�h�X�e�[�W�ł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f,-0.5f,0.0f });

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &ThirdStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGame(float deltaTime)
{
	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(), hitChecker->MapHit());

	monitoringEnemy->Update(deltaTime, player);

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Update(deltaTime, player);

		player->FoundEnemy(deltaTime, enemyPtr);

		for (auto ballBulletPtr : ballBullet)
		{
			enemyPtr->VisualAngleCake(ballBulletPtr->bullet, deltaTime);

			//�G�l�~�[���P�[�L���������Ȃ��
			if (enemyPtr->CakeFlag())
			{
				break;
			}
		}
	}

	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	}

	//�P�[�L�̃p�[�e�B�N���o��
	CakeParticlePop();

	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;

		//�T�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > 5.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}

	hitChecker->Check(thirdStageMap->GetModelHandle(), player);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	//�G�l�~�[��3�񌩂�������
	if (player->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < GOAL_POSITION_X &&
		player->GetPosition().z > GOAL_POSITION_Z)
	{
		state = State::GOAL;
		pUpdate = &ThirdStage::UpdateGoal;
	}

	for (auto particlePtr : cakeParticle)
	{
		//�p�[�e�B�N�����o���I�������
		if (particlePtr->IsParticleEnd())
		{
			DeleteCakeParticle(particlePtr);
		}
	}
}

/// <summary>
/// �S�[��
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

/// <summary>
/// �`�揈��
/// </summary>
void ThirdStage::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	thirdStageMap->Draw();

	//�Q�[����Ԃ��Q�[���ƃS�[���̎������`�悷��
	if (state == State::GAME || state == State::GOAL)
	{
		//�v���C���[�`��
		player->Draw();

		//�G�l�~�[�`��
		for (auto enemyPtr : enemy)
		{
			enemyPtr->Draw();
		}

		//�{�[���o���b�g�Ǘ��N���X�`��
		for (auto ballBulletPtr : ballBullet)
		{
			ballBulletPtr->Draw();

			uiManager->CakeGetDraw(!ballBulletPtr->cake->GetAlive());
		}
	}

	//monitoringEnemy->Draw();

	//�P�[�L�̍ďo���G�t�F�N�g�`��
	cakeEffect->Draw();

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state, player->GetPlayerCount());

	//�P�[�L�̃p�[�e�B�N���̕`��
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->GetPlayerCount());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());

	for (auto ballBulletPtr : ballBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBulletPtr->cake->GetAlive());
	}
}