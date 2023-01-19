#include "SecondStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "Player.h"
#include "Enemy.h"
#include "BallBullet.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Wall.h"
#include "HitChecker.h"
#include "SecondStageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


SecondStage::SecondStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, player(nullptr)
	, enemy()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, pUpdate(nullptr)
	, ballBullet()
	, wall(nullptr)
	, wall2(nullptr)
	, wall3(nullptr)
	, hitChecker(nullptr)
	, secondStageMap(nullptr)
	, secondStageMap2(nullptr)
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, enemyPop(false)
	, ballPop(false)
	, count(0)
{
	//�����Ȃ�
}

SecondStage::~SecondStage()
{
	//�����Ȃ�
}

void SecondStage::Initialize()
{
	//�J�����N���X
	camera = new Camera();
	camera->Initialize();

	//���C�g�N���X
	light = new Light();
	light->Initialize();

	//�w�i�N���X
	backGround = new BackGround();
	backGround->Initialize();

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

	//�ǃN���X
	wall = new Wall({ -1100.0f,30.0f,0.0f });
	wall->Initialize();

	//��2�N���X
	wall2 = new Wall({ -2000.0f,30.0f,0.0f });
	wall2->Initialize();

	//��3�N���X
	wall3 = new Wall({ -4000.0f,30.0f,0.0f });
	wall3->Initialize();

	//�Z�J���h�X�e�[�W�}�b�v�N���X
	secondStageMap = new SecondStageMap();
	secondStageMap->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();
}

void SecondStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(secondStageMap);

	for (auto ptr : enemy)
	{
		SafeDelete(ptr);
	}

	for (auto ptr : ballBullet)
	{
		SafeDelete(ptr);
	}

	SafeDelete(wall);

	SafeDelete(wall2);

	SafeDelete(wall3);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

void SecondStage::Activate()
{
	state = State::START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &SecondStage::UpdateStart;

	player->Activate();

	for (auto ptr : enemy)
	{
		ptr->Activate();
	}
}

void SecondStage::Update(float deltaTime)
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
		//覐΃I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
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
	if (!enemyPop)
	{
		Enemy* newEnemy = new Enemy(secondStageMap->GetMap());
		EntryEnemy(newEnemy);

		Enemy* newEnemy2 = new Enemy(secondStageMap->GetMap2());
		EntryEnemy(newEnemy2);

		enemyPop = true;
	}
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
/// �{�[���o���b�g���o��
/// </summary>
void SecondStage::BallBulletPop()
{
	if (!ballPop)
	{
		BallBullet* newBallBullet = new BallBullet({ -600.0f,30.0f,0.0f });
		EntryBallBullet(newBallBullet);

		/*BallBullet* newBallBullet2 = new BallBullet({ -3500.0f,30.0f,0.0f });
		EntryBallBullet(newBallBullet2);*/

		ballPop = true;
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &SecondStage::UpdateGame;
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void SecondStage::UpdateGame(float deltaTime)
{
	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->MapHit());

	EnemyPop();

	BallBulletPop();
	
	for (auto ptr : enemy)
	{
		ptr->Update(deltaTime, player);

		player->EnemyUpdate(ptr);

		
		//�G�l�~�[��3�񌩂�������
		if (ptr->GetPlayerCount() == 3)
		{
			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}

		for (auto ptra : ballBullet)
		{
			ptr->VisualAngleBall(ptra->bullet->GetPosition());
		}
	}

	for (auto ptr : ballBullet)
	{
		ptr->Update(deltaTime, hitChecker->Hit(), player->GetPosition());

		hitChecker->Check(secondStageMap->GetModel(), player, ptr->ball->GetPosition());
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < -5900)
	{
		state = State::GOAL;
		pUpdate = &SecondStage::UpdateGoal;
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

void SecondStage::Draw()
{
	//�w�i�`��
	backGround->Draw();
	
	//�}�b�v�`��
	secondStageMap->Draw();

	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	for (auto ptr : enemy)
	{
		ptr->Draw();
	}

	//�Ǖ`��
	wall->Draw();

	//��2�`��
	wall2->Draw();

	//��3�`��
	wall3->Draw();

	//�{�[���o���b�g�Ǘ��N���X�`��
	for (auto ptr : ballBullet)
	{
		ptr->Draw();
	}

	//UI�Ǘ��N���X�`��
	for (auto ptr : enemy)
	{
		uiManager->Draw(state, ptr->GetPlayerCount()); 
	}

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());

	for (auto ptr : enemy)
	{
		DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d\n", ptr->GetPlayerCount());
	}
	for (auto ptr : ballBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ptr->ball->GetAlive());
	}


	//��ʌ��ʃN���X�`��
	fadeManager->Draw();
}