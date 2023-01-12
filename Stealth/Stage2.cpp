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
	, enemy(nullptr)
	, camera(nullptr)
	, light(nullptr)
	, backGround(nullptr)
	, pUpdate(nullptr)
	, ball(nullptr)
	, wall(nullptr)
	, hitChecker(nullptr)
	, stage2Map(nullptr)
	, uiManager(nullptr)
	, fadeManager(nullptr)
	, font(0)
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
	ball = new Ball();
	ball->Initialize();

	//�ǃN���X
	wall = new Wall(ObjectBase::WALL);
	wall->Initialize();

	//�}�b�v�N���X
	stage2Map = new Stage2Map();
	stage2Map->Initialize();

	//�G�l�~�[�N���X
	enemy = new Enemy(stage2Map);
	enemy->Initialize();

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

	SafeDelete(enemy);

	SafeDelete(ball);

	SafeDelete(wall);

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
}

void Stage2::Update(float deltaTime)
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

	enemy->Update(deltaTime, player);

	player->Update(deltaTime, camera, ball, enemy);

	//hitChecker->Check(player, ball, map, enemy);

	if (ball->GetAlive())
	{
		ball->Update(hitChecker);
	}

	//fadeManager->FadeMove();

	//�G�l�~�[�ɂR�񌩂�������
	if (enemy->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::TITLE);
		return;
	}
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
	enemy->Draw();

	//�Ǖ`��
	wall->Draw();

	if (ball->GetAlive())
	{
		//�{�[���`��
		ball->Draw();
	}

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state);

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 270, GetColor(255, 0, 0), font, "Alive : %d \n(1:true 0:false)", ball->GetAlive());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());


	//��ʌ��ʃN���X�`��
	fadeManager->Draw();
}