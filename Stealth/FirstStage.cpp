#include "FirstStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "BallBullet.h"
#include "Wall.h"
#include "HitChecker.h"
#include "FirstStageMap.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "UiManager.h"
#include "FadeManager.h"


const int FirstStage::GOAL_POSITION	  = -4000;	//�S�[���̈ʒu
const int FirstStage::PARTICLE_NUMBER = 30;		//�p�[�e�B�N���̐�

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
FirstStage::FirstStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, player(nullptr)
	, enemy(nullptr)
	, pUpdate(nullptr)
	, ballBullet(nullptr)
	, wall(nullptr)
	, hitChecker(nullptr)
	, firstStageMap(nullptr)
	, cakeEffect(nullptr)
	, cakeParticle()
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, frame(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FirstStage::~FirstStage()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void FirstStage::Initialize()
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

	//�{�[���o���b�g�Ǘ��N���X
	//�{�[���̏����ʒu��ݒ�
	ballBullet = new BallBullet({ -1500.0f,30.0f,0.0f });

	//�ǃN���X
	//�ǂ̏����ʒu��ݒ�
	wall = new Wall({ -2500.0f,30.0f,0.0f });
	wall->Initialize();

	//�}�b�v�N���X
	firstStageMap = new FirstStageMap();
	firstStageMap->Initialize();

	//�P�[�L�̍ďo���G�t�F�N�g�N���X
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//�G�l�~�[�N���X
	//�G�l�~�[�ɍs���p�^�[���̃��X�g��ݒ�
	enemy = new Enemy(firstStageMap->GetMap());
	enemy->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();
}

/// <summary>
/// �I������
/// </summary>
void FirstStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(firstStageMap);

	SafeDelete(cakeEffect);

	SafeDelete(enemy);

	SafeDelete(ballBullet);

	SafeDelete(wall);

	SafeDelete(hitChecker);

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
void FirstStage::Activate()
{
	state = State::START;
	frame = 0.0f;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &FirstStage::UpdateStart;

	player->Activate();

	enemy->Activate();

	ballBullet->Activate();

	cakeEffect->Activate();

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	uiManager->Activate();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}

	//++frame;
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
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !ballBullet->bullet->GetAlive() && !ballBullet->cake->GetAlive())
	{
		//�p�[�e�B�N���̌����G���g���[����
		for (int i = 0; i < PARTICLE_NUMBER; i++)
		{
			CakeParticle* newCakeParticle = new CakeParticle(ballBullet->bullet->GetPosition());
			EntryCakeParticle(newCakeParticle);
		}
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateStart(float deltaTime)
{
	camera->Update(player->GetPosition());

	//�t�@�[�X�g�X�e�[�W�ł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f,-0.5f,0.0f });

	frame += deltaTime;

	if (frame > 1.0f)
	{
		state = State::GAME;
		pUpdate = &FirstStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGame(float deltaTime)
{
	//�P�[�L�̃p�[�e�B�N���o��
	CakeParticlePop();

	//�t�@�[�X�g�X�e�[�W�ł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player);

	enemy->VisualAngleCake(ballBullet->bullet, deltaTime);

	enemy->VisualAngleWall(wall->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy);

	ballBullet->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	
	hitChecker->Check(firstStageMap->GetModelHandle(), player);

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}
	
	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < GOAL_POSITION)
	{
		state = State::GOAL;
		pUpdate = &FirstStage::UpdateGoal;
	}

	//�G�l�~�[��3�񌩂�������
	if (player->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}

	for (auto particlePtr : cakeParticle)
	{
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
	WaitTimer(1000);

	//�X�e�[�W�I����ʂ֑J��
	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

/// <summary>
/// �`�揈��
/// </summary>
void FirstStage::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	firstStageMap->Draw();

	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	enemy->Draw();

	//�Ǖ`��
	wall->Draw();

	//�{�[���o���b�g�Ǘ��N���X�`��
	ballBullet->Draw();

	//�P�[�L�̍ďo���G�t�F�N�g�`��
	cakeEffect->Draw();

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state, player->GetPlayerCount(), hitChecker->UI());

	//�P�[�L���������Ă��邩�`��
	uiManager->CakeGetDraw(!ballBullet->cake->GetAlive());
	
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
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "CakeAlive : %d\n(1:true 0:false)", ballBullet->cake->GetAlive());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());
	DrawFormatStringToHandle(100, 620, GetColor(255, 0, 0), font, "BulletPos_X : %.0f", ballBullet->bullet->GetPosition().x);
	DrawFormatStringToHandle(100, 720, GetColor(255, 0, 0), font, "BulletPos_Z : %.0f", ballBullet->bullet->GetPosition().z);


	//��ʌ��ʃN���X�`��
	fadeManager->Draw();

}