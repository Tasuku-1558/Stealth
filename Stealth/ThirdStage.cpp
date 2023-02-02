#include "ThirdStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "BallBullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"
#include "ThirdStageMap.h"
#include "UiManager.h"


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
	, player(nullptr)
	, enemy()
	, pUpdate(nullptr)
	, ballBullet()
	, hitChecker(nullptr)
	, cakeEffect(nullptr)
	, thirdStageMap(nullptr)
	, uiManager(nullptr)
	, font(0)
	, cakePop(false)
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

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();

	//�T�[�h�X�e�[�W�}�b�v�N���X
	thirdStageMap = new ThirdStageMap();
	thirdStageMap->Initialize();

	//�G�t�F�N�g�N���X
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//�o���֐�
	BallBulletPop();
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

	SafeDelete(thirdStageMap);

	for (auto enemyPtr : enemy)
	{
		SafeDelete(enemyPtr);
	}

	for (auto ballBulletPtr : ballBullet)
	{
		SafeDelete(ballBulletPtr);
	}

	SafeDelete(hitChecker);

	SafeDelete(cakeEffect);

	SafeDelete(uiManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void ThirdStage::Activate()
{
	state = State::START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &ThirdStage::UpdateStart;

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
void ThirdStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}
}

/// <summary>
/// �{�[���o���b�g��o�^
/// </summary>
/// <param name="newBallBullet"></param>
void ThirdStage::EntryBallBullet(BallBullet* newBallBullet)
{
	ballBullet.emplace_back(newBallBullet);
}

/// <summary>
/// �{�[���o���b�g���폜
/// </summary>
/// <param name="deleteBallBullet"></param>
void ThirdStage::DeleteBallBullet(BallBullet* deleteBallBullet)
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
void ThirdStage::BallBulletPop()
{
	//�P�[�L���o�����Ă��Ȃ��Ȃ��
	if (!cakePop)
	{
		BallBullet* newBallBullet = new BallBullet({ -600.0f,30.0f,0.0f });
		EntryBallBullet(newBallBullet);

		BallBullet* newBallBullet2 = new BallBullet({ -3500.0f,30.0f,0.0f });
		EntryBallBullet(newBallBullet2);

		BallBullet* newBallBullet3 = new BallBullet({ -4000.0f,30.0f,0.0f });
		EntryBallBullet(newBallBullet3);

		cakePop = true;
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &ThirdStage::UpdateGame;
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGame(float deltaTime)
{
	//�T�[�h�X�e�[�W�ł̃��C�g�̕����̐ݒ�
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(), hitChecker->MapHit());

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

	hitChecker->Check(thirdStageMap->GetModelHandle(), player);

	//�v���C���[���S�[���n�_�ɒH�蒅������
	/*if (player->GetPosition().x < GOAL_POSITION &&
		player->GetPosition().z)
	{
		state = State::GOAL;
		pUpdate = &ThirdStage::UpdateGoal;
	}*/
}

/// <summary>
/// �S�[��
/// </summary>
/// <param name="deltaTime"></param>
void ThirdStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

/// <summary>
/// �`�揈��
/// </summary>
void ThirdStage::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	thirdStageMap->Draw();

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
}