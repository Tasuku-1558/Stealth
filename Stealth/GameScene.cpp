#include "Json.h"
#include "GameScene.h"

#include "PreCompiledHeader.h"

#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageMap.h"
#include "Player.h"
#include "Enemy.h"
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

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
	: SceneBase(SceneType::GAME)
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
	GameData::doc.ParseStream(GameData::isw);

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
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
void GameScene::Initialize()
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
	enemy = new Enemy(0, GameData::doc["EnemySpeed"]["stage1"].GetFloat());

	//�S�[���t���O�̏����ʒu��ݒ�
	goalFlag = new GoalFlag({ GameData::doc["GoalPosition"]["x"].GetFloat(),
							  GameData::doc["GoalPosition"]["y"].GetFloat(),
							  GameData::doc["GoalPosition"]["z"].GetFloat() });

	hitChecker = new HitChecker();

	uiManager = new UiManager();

	fadeManager = new FadeManager();

	//�P�[�L�̏����ʒu��ݒ�
	CakeBulletPop();

	fontHandle = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &GameScene::UpdateStart;
}

void GameScene::stage(int num)
{
	stageNo = num;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
SceneType GameScene::Update(float deltaTime)
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
void GameScene::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// �P�[�L�o���b�g�̍폜
/// </summary>
/// <param name="deleteCakeBullet"></param>
void GameScene::DeleteCakeBullet(CakeBullet* deleteCakeBullet)
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
void GameScene::CakeBulletPop()
{
	//�P�[�L�̍��W��ݒ�
	CakeBullet* newCakeBullet = new CakeBullet({ GameData::doc["CakePosition"]["stage1"]["x"].GetFloat(),
												 GameData::doc["CakePosition"]["stage1"]["y"].GetFloat(),
												 GameData::doc["CakePosition"]["stage1"]["z"].GetFloat() }, effectManager);
	EntryCakeBullet(newCakeBullet);

	CakeBullet* newCakeBullet2 = new CakeBullet({ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
												  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
												  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() }, effectManager);
	EntryCakeBullet(newCakeBullet2);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N����o�^
/// </summary>
/// <param name="newCakeParticle"></param>
void GameScene::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteCakeParticle"></param>
void GameScene::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
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
void GameScene::CakeParticlePop()
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
void GameScene::UpdateStart(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	effectManager->CreateEffect(0, player->GetPosition());

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > 1.3f)
	{
		gameState = GameState::GAME;
		pUpdate = &GameScene::UpdateGame;
	}
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void GameScene::UpdateGame(float deltaTime)
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
		pUpdate = &GameScene::UpdateOver;
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (hitChecker->FlagHit())
	{
		gameState = GameState::GOAL;
		pUpdate = &GameScene::UpdateGoal;
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
void GameScene::UpdateGoal(float deltaTime)
{
	fadeManager->FadeMove();

	//�t�F�[�h���I�������
	if (fadeManager->FadeEnd())
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
void GameScene::UpdateOver(float deltaTime)
{
	fadeManager->FadeMove();

	//�t�F�[�h���I�������
	if (fadeManager->FadeEnd())
	{
		Set::GetInstance().SetResult(!clear);

		//���U���g��ʂ֑J��
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void GameScene::Draw()
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