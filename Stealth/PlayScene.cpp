#include "PlayScene.h"
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
#include "Map.h"
#include "UiManager.h"
#include "FadeManager.h"


PlayScene::PlayScene(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, backGround(nullptr)
		, pUpdate(nullptr)
		, ball(nullptr)
		, wall(nullptr)
		, hitChecker(nullptr)
		, map(nullptr)
		, uiManager(nullptr)
		, fadeManager(nullptr)
		, font(0)
{
	//�����Ȃ�
}

PlayScene::~PlayScene()
{
	//�����Ȃ�
}

void PlayScene::Initialize()
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
	ball = new Ball({ -1500.0f,30.0f,0.0f });
	ball->Initialize();

	//�ǃN���X
	wall = new Wall(ObjectBase::WALL, { -2500.0f,30.0f,0.0f });
	wall->Initialize();

	//�}�b�v�N���X
	map = new Map();
	map->Initialize();

	//�G�l�~�[�N���X
	enemy = new Enemy(map);
	enemy->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(map);

	SafeDelete(enemy);

	SafeDelete(ball);

	SafeDelete(wall);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &PlayScene::UpdateStart;

	player->Activate();

	enemy->Activate();
}

void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateGame(float deltaTime)
{
	camera->Update(player);

	enemy->Update(deltaTime, player);

	player->Update(deltaTime, camera, ball, enemy);
	
	hitChecker->Check(player, ball/*, map*/);

	hitChecker->MapAndPlayer(map, player);

	if (ball->GetAlive())
	{
		ball->Update(hitChecker);
	}
	
	//fadeManager->FadeMove();
	
	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < -4000)
	{
		state = GOAL;
		pUpdate = &PlayScene::UpdateGoal;
	}

	//�G�l�~�[�ɂR�񌩂�������
	if (enemy->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
}

/// <summary>
/// �S�[��
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	parent->SetNextScene(SceneManager::SELECTION);
	return;
}

void PlayScene::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	map->Draw();
	
	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	enemy->Draw();

	//�Ǖ`��
	wall->Draw();

	if (ball->GetAlive())
	{
		//�{�[���`��
		ball->Draw();
	}

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state, enemy, hitChecker);

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 270, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", ball->GetAlive());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());
	

	//��ʌ��ʃN���X�`��
	fadeManager->Draw();


}