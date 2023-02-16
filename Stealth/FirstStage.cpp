#include "FirstStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
#include "CakeBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "CakeParticle.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "Set.h"
#include "SoundManager.h"


const float FirstStage::GOAL_POSITION_X	= -4000.0f;		//�S�[���̈ʒuX���W
const int   FirstStage::PARTICLE_NUMBER = 500;			//�p�[�e�B�N���̐�

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
	, cakeBullet(nullptr)
	, hitChecker(nullptr)
	, stageMap(nullptr)
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

	//�}�b�v�N���X
	//�}�b�v���f���̎�ށA�T�C�Y�A��]�l�A�ʒu����͂���
	stageMap = new StageMap(ModelManager::STAGE1, { 80.0f, 50.0f, 80.0f },
							{ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f }, { -2700.0f, -100.0f, -750.0f });

	stageMap->Initialize();

	//�G�l�~�[�N���X
	//�G�l�~�[�ɍs���p�^�[���̃��X�g��ݒ�
	enemy = new Enemy(stageMap->GetMap(0), 1000.0f);

	enemy->Initialize();

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

	//�P�[�L�o���b�g�Ǘ��N���X
	//�P�[�L�̏����ʒu��ݒ�
	cakeBullet = new CakeBullet({ -1500.0f,30.0f,0.0f });

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

	SafeDelete(stageMap);

	SafeDelete(cakeEffect);

	SafeDelete(enemy);

	SafeDelete(cakeBullet);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	for (auto particlePtr : cakeParticle)
	{
		SafeDelete(particlePtr);
		DeleteCakeParticle(particlePtr);
	}

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);

	SoundManager::GetInstance().DeleteBgm();
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

	SoundManager::GetInstance().PlayBgm();

	player->Activate();

	enemy->Activate();

	cakeBullet->Activate();

	cakeEffect->Activate();

	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Activate();
	}

	uiManager->Activate();

	fadeManager->Activate();
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
	camera->Update(player->GetPosition());

	//�t�@�[�X�g�X�e�[�W�ł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f,-0.5f,0.0f });

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > 1.3f)
	{
		state = State::GAME;
		pUpdate = &FirstStage::UpdateGame;
	}

	cakeEffect->Update(player->GetPosition().x, player->GetPosition().y - 100.0f, player->GetPosition().z);
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGame(float deltaTime)
{
	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player, hitChecker);

	enemy->VisualAngleCake(cakeBullet->bullet, deltaTime);

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	cakeBullet->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);

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
		pUpdate = &FirstStage::UpdateOver;
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < GOAL_POSITION_X)
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

	//�t���[������2.9�b�o�߂�����
	if (frame > 2.9f)
	{
		Set::GetInstance().SetResult(clear);

		SoundManager::GetInstance().StopBgm();

		//�X�e�[�W�I����ʂ֑J��
		parent->SetNextScene(SceneManager::RESULT);
		return;
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

	//�t���[������2.8�b�o�߂�����
	if (frame > 2.8f)
	{

		SoundManager::GetInstance().StopBgm();

		//�X�e�[�W�I����ʂ֑J��
		parent->SetNextScene(SceneManager::RESULT);
		return;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void FirstStage::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	stageMap->Draw();

	//�Q�[����Ԃ��Q�[���ƃS�[���ƃI�[�o�[�̎������`�悷��
	if (state == State::GAME || state == State::GOAL || state == State::OVER)
	{
		//�G�l�~�[�`��
		enemy->Draw();

		//�v���C���[�`��
		player->Draw();

		//�P�[�L�o���b�g�Ǘ��N���X�`��
		cakeBullet->Draw();
	}

	//�P�[�L�̍ďo���G�t�F�N�g�`��
	cakeEffect->Draw();

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state, player->GetPlayerCount(), hitChecker->UI());
	
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
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "CakeAlive : %d\n(1:true 0:false)", cakeBullet->cake->GetAlive());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), font, "ParticleSize : %d", cakeParticle.size());*/


}