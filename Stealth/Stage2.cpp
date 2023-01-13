#include "Stage2.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Ball.h"
#include "Wall.h"
#include "HitChecker.h"
#include "Stage2Map.h"
#include "UiManager.h"
#include "FadeManager.h"


Stage2::Stage2(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, player(nullptr)
	, enemy()
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, pUpdate(nullptr)
	, ball(nullptr)
	, ball2(nullptr)
	, wall(nullptr)
	, wall2(nullptr)
	, wall3(nullptr)
	, hitChecker(nullptr)
	, stage2Map(nullptr)
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
	, pop(false)
{
	//�����Ȃ�
}

Stage2::~Stage2()
{
	//�����Ȃ�
}

void Stage2::Initialize()
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
	player = new Player(ObjectBase::PLAYER);
	player->Initialize();

	//�{�[���N���X
	ball = new Ball({ -600.0f,30.0f,0.0f });
	ball->Initialize();

	ball2 = new Ball({ -3500.0f,30.0f,0.0f });
	ball2->Initialize();

	//�ǃN���X
	wall = new Wall(ObjectBase::WALL, { -1100.0f,30.0f,0.0f });
	wall->Initialize();

	//��2�N���X
	wall2 = new Wall(ObjectBase::WALL, { -2000.0f,30.0f,0.0f });
	wall2->Initialize();

	//��3�N���X
	wall3 = new Wall(ObjectBase::WALL, { -4000.0f,30.0f,0.0f });
	wall3->Initialize();

	//�}�b�v�N���X
	stage2Map = new Stage2Map();
	stage2Map->Initialize();

	//�G�l�~�[�N���X
	/*enemy = new Enemy(stage2Map);
	enemy->Initialize();*/

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();
}

void Stage2::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(stage2Map);

	SafeDelete(ball);

	SafeDelete(ball2);

	SafeDelete(wall);

	SafeDelete(wall2);

	SafeDelete(wall3);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

void Stage2::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &Stage2::UpdateStart;

	player->Activate();

	for (auto ptr : enemy)
	{
		SafeDelete(ptr);
		ptr->Activate();
	}
}

void Stage2::Update(float deltaTime)
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
void Stage2::EntryEnemy(Enemy* newEnemy)
{
	enemy.emplace_back(newEnemy);
}

/// <summary>
/// �G�l�~�[���폜
/// </summary>
/// <param name="deleteEnemy"></param>
void Stage2::DeleteEnemy(Enemy* deleteEnemy)
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
void Stage2::EnemyPop()
{
	if (!pop)
	{
		Enemy* newEnemy = new Enemy(stage2Map);
		EntryEnemy(newEnemy);

		Enemy* newEnemy = new Enemy();
		EntryEnemy(newEnemy);

		pop = true;
	}
	
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void Stage2::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &Stage2::UpdateGame;
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void Stage2::UpdateGame(float deltaTime)
{
	camera->Update(player);

	EnemyPop();

	for (auto ptr : enemy)
	{
		ptr->Update(deltaTime, player);

		player->Update(deltaTime, camera, ball, ptr);

		//�G�l�~�[��3�񌩂�������
		if (ptr->GetPlayerCount() == 3)
		{
			parent->SetNextScene(SceneManager::TITLE);
			return;
		}
	}

	hitChecker->Check(player, ball/*, map*/);

	if (ball->GetAlive())
	{
		ball->Update(hitChecker);
	}

	if (ball2->GetAlive())
	{
		ball2->Update(hitChecker);
	}

	//fadeManager->FadeMove();

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < -5900)
	{
		state = GOAL;
		pUpdate = &Stage2::UpdateGoal;
	}
}

/// <summary>
/// �S�[��
/// </summary>
/// <param name="deltaTime"></param>
void Stage2::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

void Stage2::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	stage2Map->Draw();

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

	if (ball->GetAlive())
	{
		//�{�[���`��
		ball->Draw();
	}

	if (ball2->GetAlive())
	{
		ball2->Draw();
	}

	//UI�Ǘ��N���X�`��
	for (auto ptr : enemy)
	{
		uiManager->Draw(state, ptr);
	}

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 270, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", ball->GetAlive());

	for (auto ptr : enemy)
	{
		DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "PlayerCount : %d", ptr->GetPlayerCount());
	}
	

	//��ʌ��ʃN���X�`��
	fadeManager->Draw();
}