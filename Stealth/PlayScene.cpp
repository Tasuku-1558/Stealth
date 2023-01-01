#include "PlayScene.h"
#include "DxLib.h"

#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "Boal.h"
#include "HitChecker.h"
#include "Map.h"
#include "UiManager.h"


PlayScene::PlayScene()
		: SceneBase()
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, pUpdate(nullptr)
		, boal(nullptr)
		, hitChecker(nullptr)
		, map(nullptr)
		, uiManager(nullptr)
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

	//�v���C���[�N���X
	player = new Player(ObjectBase::PLAYER);
	player->Initialize();

	//�{�[���N���X
	boal = new Boal();
	boal->Initialize();

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
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);

	SafeDelete(map);

	SafeDelete(enemy);

	SafeDelete(boal);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

void PlayScene::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &PlayScene::UpdateStart;

	player->Activate();

	boal->Activate();
	
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

	player->Update(deltaTime, camera, boal, enemy);
	
	hitChecker->Check(player, boal);

	if (boal->GetAlive())
	{
		boal->Update(hitChecker);
	}
	else
	{
		return;
	}
	
}

void PlayScene::Draw()
{
	//�}�b�v�`��
	map->Draw();

	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	enemy->Draw();

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state);

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 50, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Found : %d", player->GetFind());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", boal->GetAlive());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "discovery : %d", enemy->Discovery());
	DrawFormatStringToHandle(100, 450, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());

	

	if (boal->GetAlive())
	{
		//�{�[���`��
		boal->Draw();
	}
	else
	{
		return;
	}


}