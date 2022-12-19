#include "PlayScene.h"
#include "DxLib.h"

#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "Boal.h"
#include "HitChecker.h"
#include "Map.h"

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
	player = new Player();
	player->Initialize();

	//�{�[���N���X
	boal = new Boal();
	boal->Initialize();

	//�}�b�v�N���X
	map = new Map();
	map->Initialize();

	//�G�l�~�[�N���X
	enemy = new Enemy();
	enemy->Initialize(map);

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();
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

//�Q�[���J�n�O
void PlayScene::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

//�Q�[����
void PlayScene::UpdateGame(float deltaTime)
{

	camera->Update(player);

	player->Update(deltaTime, camera);

	enemy->Update(deltaTime);
	
	if (!hitChecker->Hit())
	{
		boal->Update();
	}
	else
	{
		return;
	}

	hitChecker->Check(player, boal);

}

void PlayScene::Draw()
{
	//�}�b�v�`��
	map->Draw();

	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	enemy->Draw();

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 50, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Found : %d", player->GetFind());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), font, "Boal : %d", hitChecker->Hit());

	if (!hitChecker->Hit())
	{
		//�{�[���`��
		boal->Draw();
	}
	else
	{
		return;
	}

}