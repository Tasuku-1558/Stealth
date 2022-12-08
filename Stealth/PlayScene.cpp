#include "PlayScene.h"
#include "DxLib.h"

#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "Field.h"

PlayScene::PlayScene()
		: SceneBase()
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, pUpdate(nullptr)
		, field(nullptr)
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

	//�G�l�~�[�N���X
	enemy = new Enemy();
	enemy->Initialize();

	//�f�o�b�N�p
	field = new Field();
	field->Initialize();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(player);

	SafeDelete(enemy);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);

	//�f�o�b�N�p
	SafeDelete(field);
}

void PlayScene::Activate()
{
	state = START;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &PlayScene::UpdateStart;

	player->Activate();

	enemy->Activate();

	//�f�o�b�N�p
	field->Activate();
}

void PlayScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}
}

void PlayScene::UpdateStart(float deltaTime)
{
	state = GAME;
	pUpdate = &PlayScene::UpdateGame;
}

void PlayScene::UpdateGame(float deltaTime)
{
	//camera->Update(player);

	player->Update(deltaTime);

	enemy->Update(deltaTime,field);
	
	//�f�o�b�N�p
	field->Update();
}

void PlayScene::Draw()
{
	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	enemy->Draw();

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 50, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "HP : %d", player->GetHP());

	field->Draw();
}