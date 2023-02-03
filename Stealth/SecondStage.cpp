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
#include "Wall.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "SecondStageMap.h"
#include "UiManager.h"
#include "FadeManager.h"


const int SecondStage::GOAL_POSITION = -5900;		//�S�[���̈ʒu

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
	, wall()
	, hitChecker(nullptr)
	, secondStageMap(nullptr)
	, cakeEffect(nullptr)
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

	//�G�t�F�N�g�N���X
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

	WallPop();
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

	for (auto wallPtr : wall)
	{
		SafeDelete(wallPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void SecondStage::Activate()
{
	state = State::START;

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

	++frame;
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

	BallBullet* newBallBullet2 = new BallBullet({ -3500.0f,30.0f,0.0f });
	EntryBallBullet(newBallBullet2);
}

/// <summary>
/// �ǂ�o�^
/// </summary>
/// <param name="newWall"></param>
void SecondStage::EntryWall(Wall* newWall)
{
	wall.emplace_back(newWall);
}

/// <summary>
/// �ǂ��폜
/// </summary>
/// <param name="deleteWall"></param>
void SecondStage::DeleteWall(Wall* deleteWall)
{
	//�{�[���o���b�g�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(wall.begin(), wall.end(), deleteWall);

	if (iter != wall.end())
	{
		//�{�[���o���b�g�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, wall.end() - 1);
		wall.pop_back();

		return;
	}
}

/// <summary>
/// �ǂ̏o��
/// </summary>
void SecondStage::WallPop()
{
	Wall* newWall = new Wall({ -1100.0f,30.0f,0.0f });
	EntryWall(newWall);

	Wall* newWall2 = new Wall({ -2000.0f,30.0f,0.0f });
	EntryWall(newWall2);

	Wall* newWall3 = new Wall({ -4000.0f,30.0f,0.0f });
	EntryWall(newWall3);
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
	//�Z�J���h�X�e�[�W�ł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());
	
	for (auto enemyPtr : enemy)
	{
		enemyPtr->Update(deltaTime, player);
		
		player->FoundEnemy(deltaTime, enemyPtr);

		for (auto wallPtr : wall)
		{
			enemyPtr->VisualAngleWall(wallPtr->GetPosition());
		}
		
		for (auto ballBulletPtr : ballBullet)
		{
			enemyPtr->VisualAngleCake(ballBulletPtr->bullet, deltaTime);
			
			//�G�l�~�[���P�[�L���������Ȃ��
			if (enemyPtr->CakeFlag())
			{
				break;
			}
		}

		//�G�l�~�[��3�񌩂�������
		if (enemyPtr->GetPlayerCount() == 3)
		{
			parent->SetNextScene(SceneManager::SELECTION);
			return;
		}
	}

	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	}

	hitChecker->Check(secondStageMap->GetModelHandle(), player);

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < GOAL_POSITION)
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

/// <summary>
/// �`�揈��
/// </summary>
void SecondStage::Draw()
{
	//�w�i�`��
	backGround->Draw();
	
	//�}�b�v�`��
	secondStageMap->Draw();

	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	for (auto enemyPtr : enemy)
	{
		enemyPtr->Draw();
	}

	//�Ǖ`��
	for (auto wallPtr : wall)
	{
		wallPtr->Draw();
	}

	//�{�[���o���b�g�Ǘ��N���X�`��
	for (auto ballBulletPtr : ballBullet)
	{
		ballBulletPtr->Draw();

		uiManager->CakeGetDraw(!ballBulletPtr->cake->GetAlive());
	}

	//�G�t�F�N�g�`��
	cakeEffect->Draw();

	//UI�Ǘ��N���X�`��
	for (auto enemyPtr : enemy)
	{
		uiManager->Draw(state, enemyPtr->GetPlayerCount());
	}


	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());

	for (auto enemyPtr : enemy)
	{
		DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d\n", enemyPtr->GetPlayerCount());
	}
	for (auto ballBulletPtr : ballBullet)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBulletPtr->cake->GetAlive());
	}


	//��ʌ��ʃN���X�`��
	fadeManager->Draw();
}