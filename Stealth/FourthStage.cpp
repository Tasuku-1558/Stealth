#include "FourthStage.h"
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
#include "GoalFlag.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "StageMap.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "Set.h"


const int FourthStage::PARTICLE_NUMBER = 500;			//�p�[�e�B�N���̐�

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
FourthStage::FourthStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, light(nullptr)
	, camera(nullptr)
	, backGround(nullptr)
	, stageMap(nullptr)
	, player(nullptr)
	, enemy()
	, monitoringEnemy(nullptr)
	, pUpdate(nullptr)
	, cakeBullet(nullptr)
	, goalFlag(nullptr)
	, hitChecker(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FourthStage::~FourthStage()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void FourthStage::Initialize()
{
	//���C�g�N���X
	light = new Light();
	light->Initialize();

	//�J�����N���X
	camera = new Camera();
	camera->Initialize();

	//�w�i�N���X
	backGround = new BackGround();
	backGround->Initialize();

	//�}�b�v�N���X
	//�}�b�v���f���̎�ށA�T�C�Y�A��]�l�A�ʒu����͂���
	stageMap = new StageMap(ModelManager::STAGE4, { 50.0f, 50.0f, 55.0f },
							{ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f }, { -4600.0f, -100.0f, -1300.0f });

	stageMap->Initialize();

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

	//�Ď��G�l�~�[�N���X
	//�ʒu�A�ʕ����̌����A�����̌��������
	monitoringEnemy = new MonitoringEnemy({ -4900.0f, 0.0f, 200.0f }, { -1.0f,0.0f,0.0f }, { 0.0f,0.0f,-1.0f });
	monitoringEnemy->Initialize();

	//�P�[�L�o���b�g�N���X
	cakeBullet = new CakeBullet({ -500.0f,30.0f,0.0f });
	cakeBullet->Initialize();

	//�P�[�L�̍ďo���G�t�F�N�g�N���X
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//�S�[���t���b�O�N���X
	goalFlag = new GoalFlag({ -5400.0f ,0.0f,100.0f });
	goalFlag->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();

	//�o���֐�
	EnemyPop();
}

/// <summary>
/// �I������
/// </summary>
void FourthStage::Finalize()
{
	SafeDelete(light);

	SafeDelete(camera);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(stageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
		DeleteEnemy(enemyPtr);
	}

	SafeDelete(cakeBullet);

	SafeDelete(goalFlag);

	SafeDelete(monitoringEnemy);

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
		DeleteCakeParticle(particlePtr);
	}

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void FourthStage::Activate()
{
	state = State::START;

	frame = 0.0f;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &FourthStage::UpdateStart;

	player->Activate();

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Activate();
	}

	cakeBullet->Activate();

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	monitoringEnemy->Activate();

	cakeEffect->Activate();

	uiManager->Activate();

	fadeManager->Activate();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::Update(float deltaTime)
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
void FourthStage::EntryEnemy(Enemy* newEnemy)
{
	enemy.emplace_back(newEnemy);
}

/// <summary>
/// �G�l�~�[���폜
/// </summary>
/// <param name="deleteEnemy"></param>
void FourthStage::DeleteEnemy(Enemy* deleteEnemy)
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
void FourthStage::EnemyPop()
{
	Enemy* newEnemy = new Enemy(stageMap->GetMap(5), 300.0f);
	EntryEnemy(newEnemy);

	Enemy* newEnemy2 = new Enemy(stageMap->GetMap(6), 800.0f);
	EntryEnemy(newEnemy2);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N����o�^
/// </summary>
/// <param name="newCakeParticle"></param>
void FourthStage::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteCakeParticle"></param>
void FourthStage::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
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
void FourthStage::CakeParticlePop()
{
	//�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u���p�[�e�B�N�����o�Ă��Ȃ��Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && cakeBullet->bullet->GetAlive() && !cakeBullet->cake->GetAlive() && !particleFlag)
	{
		//�p�[�e�B�N���̌����G���g���[����
		for (int i = 0; i < PARTICLE_NUMBER; i++)
		{
			CakeParticle* newCakeParticle = new CakeParticle(cakeBullet->bullet->GetPosition());
			EntryCakeParticle(newCakeParticle);
		}

		particleFlag = true;
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateStart(float deltaTime)
{
	camera->Update(player->GetPosition());

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &FourthStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateGame(float deltaTime)
{
	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(), hitChecker->MapHit());

	for (auto enemyPtr : enemy)
	{
		enemyPtr->Update(deltaTime, player, hitChecker);

		//���񂵂Ă���G�l�~�[�Ɍ���������
		player->FoundEnemy(deltaTime, enemyPtr->Spotted());

		enemyPtr->VisualAngleCake(cakeBullet->bullet, deltaTime);

		//�G�l�~�[���P�[�L���������Ȃ��
		if (enemyPtr->CakeFlag())
		{
			break;
		}
	}

	//�Ď����Ă���G�l�~�[�Ɍ���������
	monitoringEnemy->Update(deltaTime, player, hitChecker);

	player->FoundEnemy(deltaTime, monitoringEnemy->Spotted());

	cakeBullet->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);

	goalFlag->Update(deltaTime);

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

	hitChecker->Check(stageMap->GetModelHandle(), player, goalFlag->GetPosition());

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	//�G�l�~�[��3�񌩂�������
	if (player->GetPlayerCount() == 3)
	{
		state = State::OVER;
		pUpdate = &FourthStage::UpdateOver;
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (hitChecker->FlagHit())
	{
		state = State::GOAL;
		pUpdate = &FourthStage::UpdateGoal;
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
void FourthStage::UpdateGoal(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	Set::GetInstance().SetResult(clear);

	//�t���[������2.9�b�o�߂�����
	if (frame > 2.9f)
	{
		//�X�e�[�W�I����ʂ֑J��
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateOver(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	Set::GetInstance().SetResult(!clear);

	//�t���[������2.8�b�o�߂�����
	if (frame > 2.8f)
	{
		//�X�e�[�W�I����ʂ֑J��
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void FourthStage::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	stageMap->Draw();

	//�Q�[����Ԃ��Q�[���ƃS�[���ƃI�[�o�[�̎������`�悷��
	if (state == State::GAME || state == State::GOAL || state == State::OVER)
	{
		//�v���C���[�`��
		player->Draw();

		//�G�l�~�[�`��
		for (auto enemyPtr : enemy)
		{
			enemyPtr->Draw();
		}

		//�Ď��G�l�~�[�̕`��
		monitoringEnemy->Draw();

		//�P�[�L�o���b�g�Ǘ��N���X�`��
		cakeBullet->Draw();

		//�S�[���t���b�O�̕`��
		goalFlag->Draw();
	}

	//�P�[�L�̍ďo���G�t�F�N�g�`��
	cakeEffect->Draw();

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state, player->GetPlayerCount());

	//�P�[�L���������Ă��邩�`��
	uiManager->CakeGetDraw(cakeBullet->CakeGet());

	//�P�[�L�̃p�[�e�B�N���̕`��
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	//��ʌ��ʃN���X�`��
	fadeManager->Draw();

	//�f�o�b�N�p
	/*DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->GetPlayerCount());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());

	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", cakeBullet->cake->GetAlive());*/

}