#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "FireWorksParticle.h"

char GameClear[] = { "GAME CLEAR" };


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, fireWorksParticle(nullptr)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Initialize()
{
	for (int i = 0; i < 50; i++)
	{
		fireWorksParticle = new FireWorksParticle({ 100.0f ,0.0f,-1000.0f });
		fireWorksParticle->Initialize();
	}
}

/// <summary>
/// �I������
/// </summary>
void ResultScene::Finalize()
{
	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);

	SafeDelete(fireWorksParticle);
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Activate()
{
	font = CreateFontToHandle("Oranienbaum", 150, 1);

	fireWorksParticle->Activate();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	fireWorksParticle->Update(deltaTime);
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Draw()
{
	DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameClear);

	fireWorksParticle->Draw();
}