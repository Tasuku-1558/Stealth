#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "FirstStage.h"

#include "DxLib.h"
#include "PreCompiledHeader.h"
#include <fstream>

#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "CakeParticle.h"
#include "EffectManager.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "Set.h"

//�f�o�b�N�p
#define DEBUG

namespace Json
{
	const char* filePath = "Data/Json/GameData.json";

	//json�t�@�C���̉��
	//��́E�E�E�L�[�̖��O���R���e���c�Ƃ��Ĉ�����悤�ɂ��邽�߂̍�Ɓi��@doc[�L�[].GetInt()�ȂǂŎg����悤�ɁH
	std::ifstream ifs(filePath);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
}
/// <summary>
/// �R���X�g���N�^
/// </summary>
FirstStage::FirstStage()
	: SceneBase(SceneType::PLAY)
	, gameState(GameState::START)
	, pUpdate(nullptr)
	, fontHandle(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
	, stageNo(0)
	, PARTICLE_NUMBER(500)
	, PLAYER_HP(2)
{
	Json::doc.ParseStream(Json::isw);

	Initialize();
	Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FirstStage::~FirstStage()
{
	DeleteFontToHandle(fontHandle);

	for (auto CakeBulletPtr : cakeBullet)
	{
		DeleteCakeBullet(CakeBulletPtr);
	}
}

/// <summary>
/// ����������
/// </summary>
void FirstStage::Initialize()
{
	camera = new Camera();

	light = new Light();
	
	backGround = new BackGround();

	//�}�b�v���f���̎�ށA�T�C�Y�A��]�l�A�ʒu����͂���
	stageMap = new StageMap(ModelManager::STAGE1, { 80.0f, 50.0f, 80.0f },
		{ 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }, { -780.0f, -100.0f, 2400.0f });

	effectManager = new EffectManager();

	player = new Player(effectManager);

	//�G�l�~�[�ɍs���p�^�[���̃i���o�[�ƃX�s�[�h��ݒ�
	enemy = new Enemy(0, Json::doc["Position"]["x"].GetFloat()/*1000.0f*/);

	//�S�[���t���O�̏����ʒu��ݒ�
	goalFlag = new GoalFlag({ -50.0f ,0.0f,3700.0f });

	hitChecker = new HitChecker();

	uiManager = new UiManager();

	fadeManager = new FadeManager();

	//�P�[�L�̏����ʒu��ݒ�
	CakeBulletPop();
}

void FirstStage::stage(int num)
{
	stageNo = num;
}

/// <summary>
/// ����������
/// </summary>
void FirstStage::Activate()
{
	fontHandle = CreateFontToHandle("Oranienbaum", 50, 1);

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
/// �P�[�L�o���b�g��o�^
/// </summary>
/// <param name="newCakeBullet"></param>
void FirstStage::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// �P�[�L�o���b�g�̍폜
/// </summary>
/// <param name="deleteCakeBullet"></param>
void FirstStage::DeleteCakeBullet(CakeBullet* deleteCakeBullet)
{
	//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(cakeBullet.begin(), cakeBullet.end(), deleteCakeBullet);

	if (iter != cakeBullet.end())
	{
		//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, cakeBullet.end() - 1);
		cakeBullet.pop_back();

		return;
	}
}

/// <summary>
/// �P�[�L�o���b�g�̏o��
/// </summary>
void FirstStage::CakeBulletPop()
{
	//�P�[�L�̍��W��ݒ�
	CakeBullet* newCakeBullet = new CakeBullet({ 0.0f,30.0f,1500.0f }, effectManager);
	EntryCakeBullet(newCakeBullet);

	CakeBullet* newCakeBullet2 = new CakeBullet({ 0.0f,30.0f,1000.0f }, effectManager);
	EntryCakeBullet(newCakeBullet2);
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
	for (auto CakeBulletPtr : cakeBullet)
	{
		//�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u���p�[�e�B�N�����o�Ă��Ȃ��Ȃ��
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && CakeBulletPtr->bullet->GetAlive() && !CakeBulletPtr->cake->GetAlive() && !particleFlag)
		{
			//�p�[�e�B�N���̌����G���g���[����
			for (int i = 0; i < PARTICLE_NUMBER; i++)
			{
				CakeParticle* newCakeParticle = new CakeParticle(CakeBulletPtr->bullet->GetPosition());
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
void FirstStage::UpdateStart(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	effectManager->CreateRepopEffect(player->GetPosition());

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > 1.3f)
	{
		gameState = GameState::GAME;
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

	player->Update(deltaTime, hitChecker->Back(), hitChecker->MapHit());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	enemy->Update(deltaTime, player);

	for (auto CakeBulletPtr : cakeBullet)
	{
		enemy->VisualAngleCake(CakeBulletPtr->bullet, deltaTime);

		if (enemy->CakeFlag())
		{
			break;
		}
	}

	for (auto CakeBulletPtr : cakeBullet)
	{
		CakeBulletPtr->Update(deltaTime, player);
	}

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
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	hitChecker->Check(stageMap->GetModelHandle(), player, &cakeBullet, /*&enemy,*/ goalFlag);
	hitChecker->EnemyAndPlayer(player, enemy);
	
	//�G�l�~�[��2�񌩂�������
	if (player->FindCount() == PLAYER_HP)
	{
		gameState = GameState::OVER;
		pUpdate = &FirstStage::UpdateOver;
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (hitChecker->FlagHit())
	{
		gameState = GameState::GOAL;
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
	if (gameState != GameState::START)
	{
		enemy->Draw();

		player->Draw();
		
		for (auto CakeBulletPtr : cakeBullet)
		{
			CakeBulletPtr->Draw();

			uiManager->CakeGetDraw(CakeBulletPtr->CakeGet());
		}
	}

	goalFlag->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UI());
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	fadeManager->Draw();

	//�f�o�b�N�p
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), fontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), fontHandle, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), fontHandle, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 520, GetColor(255, 0, 0), fontHandle, "ParticleSize : %d", cakeParticle.size());
	DrawFormatStringToHandle(100, 600, GetColor(255, 0, 0), fontHandle, "stage : %d", stageNo);
#endif // DEBUG
}