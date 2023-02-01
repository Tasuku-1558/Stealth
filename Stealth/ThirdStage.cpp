#include "ThirdStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "Light.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
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
}