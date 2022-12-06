#include "PlayScene.h"
#include "DxLib.h"

#include "Common.h"
#include "Player.h"
#include "Camera.h"

PlayScene::PlayScene()
		: SceneBase()
		, state()
		, player(nullptr)
		, camera(nullptr)
		, pUpdate(nullptr)
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

	//�v���C���[�N���X
	player = new Player();
	player->Initialize();
}

void PlayScene::Finalize()
{
	SafeDelete(camera);

	SafeDelete(player);
}

void PlayScene::Activate()
{
	state = START;
	pUpdate = &PlayScene::UpdateStart;

	player->Activate();
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
	camera->Update();

	player->Update(deltaTime);
	
}

void PlayScene::Draw()
{
	//�v���C���[�`��
	player->Draw();

	camera->Draw();
}