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
#include "CakeBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "StageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


const float ThirdStage::GOAL_POSITION_X = -2800.0f;		//�S�[���̈ʒuX���W
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
	, stageMap(nullptr)
	, player(nullptr)
	, enemy()
	, monitoringEnemy()
	, pUpdate(nullptr)
	, cakeBullet()
	, hitChecker(nullptr)
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

	//�}�b�v�N���X
	//�}�b�v���f���̎�ށA�T�C�Y�A��]�l�A�ʒu����͂���
	stageMap = new StageMap(ModelManager::STAGE3, { 50.0f, 50.0f, 55.0f }, 
							{ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f }, { -2600.0f, -100.0f, 2650.0f });
	stageMap->Initialize();

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

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
	CakeBulletPop();

	EnemyPop();

	MonitoringEnemyPop();
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

	SafeDelete(stageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
	}

	for (auto cakeBulletPtr : cakeBullet)
	{
		SafeDelete(cakeBulletPtr);
	}

	for (auto monitoringEnemyPtr : monitoringEnemy)
	{
		SafeDelete(monitoringEnemyPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
	}

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void ThirdStage::Activate()
{
	state = State::START;

	frame = 0.0f;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &ThirdStage::UpdateStart;

	player->Activate();

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Activate();
	}

	for (auto cakeBulletPtr : cakeBullet)
	{
		cakeBulletPtr->Activate();
	}

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	for (auto monitoringEnemyPtr : monitoringEnemy)
	{
		monitoringEnemyPtr->Activate();
	}

	cakeEffect->Activate();

	uiManager->Activate();

	fadeManager->Activate();
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
	Enemy* newEnemy = new Enemy(stageMap->GetMap(3));
	EntryEnemy(newEnemy);

	Enemy* newEnemy2 = new Enemy(stageMap->GetMap(4));
	EntryEnemy(newEnemy2);
}

/// <summary>
/// �Ď��G�l�~�[�̓o�^
/// </summary>
/// <param name="newMonitoringEnemy"></param>
void ThirdStage::EntryMonitoringEnemy(MonitoringEnemy* newMonitoringEnemy)
{
	monitoringEnemy.emplace_back(newMonitoringEnemy);
}

/// <summary>
/// �Ď��G�l�~�[�̍폜
/// </summary>
/// <param name="deleteMonitoringEnemy"></param>
void ThirdStage::DeleteMonitoringEnemy(MonitoringEnemy* deleteMonitoringEnemy)
{
	//�Ď��G�l�~�[�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(monitoringEnemy.begin(), monitoringEnemy.end(), deleteMonitoringEnemy);

	if (iter != monitoringEnemy.end())
	{
		//�Ď��G�l�~�[�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, monitoringEnemy.end() - 1);
		monitoringEnemy.pop_back();

		return;
	}
}

/// <summary>
/// �Ď��G�l�~�[�̏o��
/// </summary>
void ThirdStage::MonitoringEnemyPop()
{
	MonitoringEnemy* newMonitoringEnemy = new MonitoringEnemy({ -2850.0f, 0.0f, 3000.0f }, { 1.0f,0.0f,0.0f });
	EntryMonitoringEnemy(newMonitoringEnemy);

	MonitoringEnemy* newMonitoringEnemy2 = new MonitoringEnemy({ -1000.0f, 0.0f, 3000.0f }, { -1.0f,0.0f,0.0f });
	EntryMonitoringEnemy(newMonitoringEnemy2);
}

/// <summary>
/// �P�[�L�o���b�g��o�^
/// </summary>
/// <param name="newCakeBullet"></param>
void ThirdStage::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// �P�[�L�o���b�g���폜
/// </summary>
/// <param name="deleteCakeBullet"></param>
void ThirdStage::DeleteCakeBullet(CakeBullet* deleteCakeBullet)
{
	//�P�[�L�o���b�g�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(cakeBullet.begin(), cakeBullet.end(), deleteCakeBullet);

	if (iter != cakeBullet.end())
	{
		//�P�[�L�o���b�g�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, cakeBullet.end() - 1);
		cakeBullet.pop_back();

		return;
	}
}

/// <summary>
/// �P�[�L�o���b�g�̏o��
/// </summary>
void ThirdStage::CakeBulletPop()
{
	CakeBullet* newCakeBullet = new CakeBullet({ -1500.0f,30.0f,0.0f });
	EntryCakeBullet(newCakeBullet);

	CakeBullet* newCakeBullet2 = new CakeBullet({ -2000.0f,30.0f,1800.0f });
	EntryCakeBullet(newCakeBullet2);
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
	for (auto cakeBulletPtr : cakeBullet)
	{
		//�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u���p�[�e�B�N�����o�Ă��Ȃ��Ȃ��
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && cakeBulletPtr->bullet->GetAlive() && !cakeBulletPtr->cake->GetAlive() && !particleFlag)
		{
			//�p�[�e�B�N���̌����G���g���[����
			for (int i = 0; i < PARTICLE_NUMBER; i++)
			{
				CakeParticle* newCakeParticle = new CakeParticle(cakeBulletPtr->bullet->GetPosition());
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

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Update(deltaTime, player);

		//���񂵂Ă���G�l�~�[�Ɍ���������
		player->FoundEnemy(deltaTime, enemyPtr->Spotted());

		for (auto cakeBulletPtr : cakeBullet)
		{
			enemyPtr->VisualAngleCake(cakeBulletPtr->bullet, deltaTime);

			//monitoringEnemy->VisualAngleCake(cakeBulletPtr->bullet, deltaTime);

			//�G�l�~�[���P�[�L���������Ȃ��
			if (enemyPtr->CakeFlag())
			{
				break;
			}
		}
	}

	for (auto monitoringEnemyPtr : monitoringEnemy)
	{
		//�Ď����Ă���G�l�~�[�Ɍ���������
		monitoringEnemyPtr->Update(deltaTime, player);

		player->FoundEnemy(deltaTime, monitoringEnemyPtr->Spotted());
	}

	for (auto cakeBulletPtr : cakeBullet)
	{
		cakeBulletPtr->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	}

	//�P�[�L�̃p�[�e�B�N���o��
	CakeParticlePop();

	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;

		//5�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > 5.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}

	hitChecker->Check(stageMap->GetModelHandle(), player);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	//�G�l�~�[��3�񌩂�������
	if (player->GetPlayerCount() == 3)
	{
		state = State::OVER;
		pUpdate = &ThirdStage::UpdateOver;
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
	frame += deltaTime;

	fadeManager->FadeMove();

	//�t���[������2.9�b�o�߂�����
	if (frame > 2.9f)
	{
		//�X�e�[�W�I����ʂ֑J��
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}
}

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateOver(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//�t���[������2.8�b�o�߂�����
	if (frame > 2.8f)
	{
		//�X�e�[�W�I����ʂ֑J��
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ThirdStage::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	stageMap->Draw();

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

		//�Ď��G�l�~�[�̕`��
		for (auto monitoringEnemyPtr : monitoringEnemy)
		{
			monitoringEnemyPtr->Draw();
		}

		//�P�[�L�o���b�g�Ǘ��N���X�`��
		for (auto cakeBulletPtr : cakeBullet)
		{
			cakeBulletPtr->Draw();

			uiManager->CakeGetDraw(!cakeBulletPtr->cake->GetAlive());
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

	//��ʌ��ʃN���X�`��
	fadeManager->Draw();

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->GetPlayerCount());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());

	for (auto cakeBulletPtr : cakeBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", cakeBulletPtr->cake->GetAlive());
	}
}