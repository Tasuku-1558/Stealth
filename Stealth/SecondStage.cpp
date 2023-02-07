#include "SecondStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "BallBullet.h"
#include "HitChecker.h"
#include "CakeParticle.h"
#include "CakeRepopEffect.h"
#include "SecondStageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


const float SecondStage::GOAL_POSITION_X = -5700.0f;	//�S�[���̈ʒu
const int   SecondStage::PARTICLE_NUMBER = 500;			//�p�[�e�B�N���̐�


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
SecondStage::SecondStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy()
	, pUpdate(nullptr)
	, ballBullet()
	, hitChecker(nullptr)
	, secondStageMap(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
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
SecondStage::~SecondStage()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void SecondStage::Initialize()
{
	//�J�����N���X
	camera = new Camera();
	camera->Initialize();

	//���C�g�N���X
	light = new Light();

	//�w�i�N���X
	backGround = new BackGround();
	backGround->Initialize();

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

	//�Z�J���h�X�e�[�W�}�b�v�N���X
	secondStageMap = new SecondStageMap();
	secondStageMap->Initialize();

	//�P�[�L�̍ďo���G�t�F�N�g�N���X
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();

	//�o���֐�
	EnemyPop();

	BallBulletPop();
}

/// <summary>
/// �I������
/// </summary>
void SecondStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(secondStageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
		DeleteEnemy(enemyPtr);
	}

	for (auto ballBulletPtr : ballBullet)
	{
		SafeDelete(ballBulletPtr);
		DeleteBallBullet(ballBulletPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
	}

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void SecondStage::Activate()
{
	state = State::START;

	frame = 0.0f;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &SecondStage::UpdateStart;

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
void SecondStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}

	//++frame;
}

/// <summary>
/// �G�l�~�[��o�^
/// </summary>
/// <param name="newEnemy"></param>
void SecondStage::EntryEnemy(Enemy* newEnemy)
{
	enemy.emplace_back(newEnemy);
}

/// <summary>
/// �G�l�~�[���폜
/// </summary>
/// <param name="deleteEnemy"></param>
void SecondStage::DeleteEnemy(Enemy* deleteEnemy)
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
void SecondStage::EnemyPop()
{
	Enemy* newEnemy = new Enemy(secondStageMap->GetMap());
	EntryEnemy(newEnemy);

	Enemy* newEnemy2 = new Enemy(secondStageMap->GetMap2());
	EntryEnemy(newEnemy2);
}

/// <summary>
/// �{�[���o���b�g��o�^
/// </summary>
/// <param name="newBallBullet"></param>
void SecondStage::EntryBallBullet(BallBullet* newBallBullet)
{
	ballBullet.emplace_back(newBallBullet);
}

/// <summary>
/// �{�[���o���b�g���폜
/// </summary>
/// <param name="deleteBallBullet"></param>
void SecondStage::DeleteBallBullet(BallBullet* deleteBallBullet)
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
void SecondStage::BallBulletPop()
{
	BallBullet* newBallBullet = new BallBullet({ -600.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet);

	BallBullet* newBallBullet2 = new BallBullet({ -3000.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet2);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N����o�^
/// </summary>
/// <param name="newCakeParticle"></param>
void SecondStage::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteCakeParticle"></param>
void SecondStage::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
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
void SecondStage::CakeParticlePop()
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
void SecondStage::UpdateStart(float deltaTime)
{
	camera->Update(player->GetPosition());

	//�t�@�[�X�g�X�e�[�W�ł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f,-0.5f,0.0f });

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &SecondStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y , player->GetPosition().z);
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateGame(float deltaTime)
{
	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());
	
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

	hitChecker->Check(secondStageMap->GetModelHandle(), player);

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
	if (player->GetPosition().x < GOAL_POSITION_X)
	{
		state = State::GOAL;
		pUpdate = &SecondStage::UpdateGoal;
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
void SecondStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

/// <summary>
/// �`�揈��
/// </summary>
void SecondStage::Draw()
{
	//�w�i�`��
	backGround->Draw();
	
	//�}�b�v�`��
	secondStageMap->Draw();

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


	//��ʌ��ʃN���X�`��
	fadeManager->Draw();
}