#include "FirstStage.h"
#include "DxLib.h"
#include "PreCompiledHeader.h"

#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "RepopEffect.h"
#include "CakeParticle.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "Set.h"

//�f�o�b�N�p
#define DEBUG


/// <summary>
/// �R���X�g���N�^
/// </summary>
FirstStage::FirstStage()
	: SceneBase(SceneType::PLAY)
	, state()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy(nullptr)
	, pUpdate(nullptr)
	, cakeBullet(nullptr)
	, hitChecker(nullptr)
	, stageMap(nullptr)
	, goalFlag(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
	, stageNo(0)
	, PARTICLE_NUMBER(500)
	, PLAYER_HP(2)
{
	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FirstStage::~FirstStage()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void FirstStage::Initialize()
{
	camera = new Camera();

	light = new Light();
	
	backGround = new BackGround();

	stageMap = new StageMap();

	if (stageMap->GetStage() == 1)
	{
		//�}�b�v���f���̎�ށA�T�C�Y�A��]�l�A�ʒu����͂���
		stageMap->Initialize(ModelManager::STAGE1, { 80.0f, 50.0f, 80.0f },
			{ 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }, { -780.0f, -100.0f, 2400.0f });

		//�G�l�~�[�ɍs���p�^�[���̃��X�g�ƃX�s�[�h��ݒ�
		enemy = new Enemy(stageMap->GetMap(1), 1000.0f);

		//�P�[�L�̏����ʒu��ݒ�
		cakeBullet = new CakeBullet({ 0.0f,30.0f,1500.0f });

		goalFlag = new GoalFlag({ -50.0f ,0.0f,3700.0f });
	}
	if (stageMap->GetStage() == 2)
	{
		//�}�b�v���f���̎�ށA�T�C�Y�A��]�l�A�ʒu����͂���
		stageMap->Initialize(ModelManager::STAGE2, { 80.0f, 60.0f, 80.0f },
						{ 0.0f, 0.0f, 0.0f }, { -7000.0f, -100.0f, -2900.0f });
		//�G�l�~�[�ɍs���p�^�[���̃��X�g�ƃX�s�[�h��ݒ�
		enemy = new Enemy(stageMap->GetMap(0), 1000.0f);

		//�P�[�L�̏����ʒu��ݒ�
		cakeBullet = new CakeBullet({ -1500.0f,30.0f,0.0f });

		//�S�[���t���O�̈ʒu��ݒ�
		goalFlag = new GoalFlag({ -4000.0f ,0.0f,0.0f });
	}

	player = new Player();

	cakeEffect = new RepopEffect();

	hitChecker = new HitChecker();

	uiManager = new UiManager();

	fadeManager = new FadeManager();
}

/// <summary>
/// �I������
/// </summary>
void FirstStage::Finalize()
{
	/*SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(stageMap);

	SafeDelete(enemy);

	SafeDelete(cakeBullet);

	SafeDelete(goalFlag);

	SafeDelete(player);

	SafeDelete(cakeEffect);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);*/

	for (auto particlePtr : cakeParticle)
	{
		DeleteCakeParticle(particlePtr);
		//SafeDelete(particlePtr);
	}

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void FirstStage::Activate()
{
	font = CreateFontToHandle("Oranienbaum", 50, 1);

	state = State::START;
	pUpdate = &FirstStage::UpdateStart;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
SceneType FirstStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V

		return nowSceneType;
	}
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N����o�^
/// </summary>
/// <param name="newCakeParticle"></param>
void FirstStage::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteCakeParticle"></param>
void FirstStage::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
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
void FirstStage::CakeParticlePop()
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
void FirstStage::UpdateStart(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	cakeEffect->Update(player->GetPosition());

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &FirstStage::UpdateGame;
	}
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGame(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player);

	enemy->VisualAngleCake(cakeBullet->bullet, deltaTime);

	player->Update(deltaTime, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	cakeBullet->Update(deltaTime, player, cakeEffect);

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
	
	hitChecker->Check(stageMap->GetModelHandle(), player, goalFlag);

	hitChecker->EnemyAndPlayer(player, enemy);

	hitChecker->CakeAndPlayer(player, cakeBullet->cake);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}
	
	//�G�l�~�[��2�񌩂�������
	if (player->FindCount() == PLAYER_HP)
	{
		state = State::OVER;
		pUpdate = &FirstStage::UpdateOver;
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (hitChecker->FlagHit())
	{
		state = State::GOAL;
		pUpdate = &FirstStage::UpdateGoal;
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
void FirstStage::UpdateGoal(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//�t���[������3.4�b�o�߂�����
	if (frame > 3.4f)
	{
		Set::GetInstance().SetResult(clear);

		//���U���g��ʂ֑J��
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateOver(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//�t���[������3.4�b�o�߂�����
	if (frame > 3.4f)
	{
		Set::GetInstance().SetResult(!clear);

		//���U���g��ʂ֑J��
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void FirstStage::Draw()
{
	backGround->Draw();

	stageMap->Draw();

	//�Q�[����Ԃ��X�^�[�g�ł͂Ȃ��Ȃ�Ε`�悷��
	if (state != State::START)
	{
		enemy->Draw();

		player->Draw();
		
		cakeBullet->Draw();

		goalFlag->Draw();
	}

	cakeEffect->Draw();

	uiManager->Draw(state, player->FindCount(), hitChecker->UI());
	
	uiManager->CakeGetDraw(cakeBullet->CakeGet());
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	fadeManager->Draw();

	//�f�o�b�N�p
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "CakeAlive : %d\n(1:true 0:false)", cakeBullet->cake->GetAlive());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());
#endif // DEBUG
}