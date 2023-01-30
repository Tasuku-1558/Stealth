#include "FirstStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "BallBullet.h"
#include "Wall.h"
#include "HitChecker.h"
#include "FirstStageMap.h"
#include "CakeRepopEffect.h"
#include "UiManager.h"
#include "FadeManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
FirstStage::FirstStage(SceneManager* const sceneManager)
		: SceneBase(sceneManager)
		, state()
		, player(nullptr)
		, enemy(nullptr)
		, camera(nullptr)
		, light(nullptr)
		, backGround(nullptr)
		, pUpdate(nullptr)
		, ballBullet(nullptr)
		, wall(nullptr)
		, hitChecker(nullptr)
		, firstStageMap(nullptr)
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
FirstStage::~FirstStage()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void FirstStage::Initialize()
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

	//�{�[���o���b�g�Ǘ��N���X
	//�{�[���̏����ʒu��ݒ�
	ballBullet = new BallBullet({ -1500.0f,30.0f,0.0f });

	//�ǃN���X
	//�ǂ̏����ʒu��ݒ�
	wall = new Wall({ -2500.0f,30.0f,0.0f });
	wall->Initialize();

	//�}�b�v�N���X
	firstStageMap = new FirstStageMap();
	firstStageMap->Initialize();

	//�G�t�F�N�g�N���X
	cakeEffect = new CakeRepopEffect();
	cakeEffect->Initialize();

	//�G�l�~�[�N���X
	//�G�l�~�[�ɍs���p�^�[���̃��X�g��ݒ�
	enemy = new Enemy(firstStageMap->GetMap());
	enemy->Initialize();

	//�q�b�g�`�F�b�J�[�N���X
	hitChecker = new HitChecker();

	//UI�Ǘ��N���X
	uiManager = new UiManager();
	uiManager->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();
}

/// <summary>
/// �I������
/// </summary>
void FirstStage::Finalize()
{
	SafeDelete(camera);

	SafeDelete(light);

	SafeDelete(backGround);

	SafeDelete(player);

	SafeDelete(firstStageMap);

	SafeDelete(cakeEffect);

	SafeDelete(enemy);

	SafeDelete(ballBullet);

	SafeDelete(wall);

	SafeDelete(hitChecker);

	SafeDelete(uiManager);

	SafeDelete(fadeManager);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);
}

/// <summary>
/// ����������
/// </summary>
void FirstStage::Activate()
{
	state = State::START;
	frame = 0;

	font = CreateFontToHandle("Oranienbaum", 50, 1);

	pUpdate = &FirstStage::UpdateStart;

	player->Activate();

	enemy->Activate();

	ballBullet->Activate();

	cakeEffect->Activate();

	uiManager->Activate();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}

	++frame;
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateStart(float deltaTime)
{
	state = State::GAME;
	pUpdate = &FirstStage::UpdateGame;

}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGame(float deltaTime)
{
	light->Update({ 0.0f,-0.5f,0.0f });

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player);

	enemy->VisualAngleBall(ballBullet->bullet, deltaTime);

	enemy->VisualAngleWall(wall->GetPosition());

	player->Update(deltaTime, camera, hitChecker->Back(),hitChecker->MapHit());

	player->FoundEnemy(enemy);

	ballBullet->Update(deltaTime, player->GetPosition(), hitChecker, cakeEffect);
	
	hitChecker->Check(firstStageMap->GetModel(), player);
	
	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (player->GetPosition().x < -4000)
	{
		state = State::GOAL;
		pUpdate = &FirstStage::UpdateGoal;
	}

	//�G�l�~�[��3�񌩂�������
	if (enemy->GetPlayerCount() == 3)
	{
		parent->SetNextScene(SceneManager::SELECTION);
		return;
	}
}

/// <summary>
/// �S�[��
/// </summary>
/// <param name="deltaTime"></param>
void FirstStage::UpdateGoal(float deltaTime)
{
	WaitTimer(1000);

	//�X�e�[�W�I����ʂ֑J��
	parent->SetNextScene(SceneManager::SELECTION);
	return;

}

/// <summary>
/// �`�揈��
/// </summary>
void FirstStage::Draw()
{
	//�w�i�`��
	backGround->Draw();

	//�}�b�v�`��
	firstStageMap->Draw();
	
	//�v���C���[�`��
	player->Draw();

	//�G�l�~�[�`��
	enemy->Draw();

	//�Ǖ`��
	wall->Draw();

	//�{�[���o���b�g�Ǘ��N���X�`��
	ballBullet->Draw();

	//�G�t�F�N�g�`��
	cakeEffect->Draw();

	//UI�Ǘ��N���X�`��
	uiManager->Draw(state, enemy->GetPlayerCount(), hitChecker->UI());

	uiManager->CakeGetDraw(!ballBullet->ball->GetAlive());
	

	//�f�o�b�N�p
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "X : %d", player->GetX());
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), font, "Z : %d", player->GetZ());
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), font, "Speed : %d", player->GetSpeed());
	DrawFormatStringToHandle(100, 300, GetColor(255, 0, 0), font, "PlayerCount : %d", enemy->GetPlayerCount());
	DrawFormatStringToHandle(100, 400, GetColor(255, 0, 0), font, "BallAlive : %d\n(1:true 0:false)", ballBullet->ball->GetAlive());


	//��ʌ��ʃN���X�`��
	fadeManager->Draw();

}