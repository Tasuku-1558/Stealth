#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "FireWorksParticle.h"
#include "FadeManager.h"
#include "Set.h"


char GameClear[] = { "GAME CLEAR" };
char GameOver[]  = { "GAME OVER" };


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, frame(0.0f)
	, fireWorksParticle()
	, pUpdate(nullptr)
	, particleFlag(false)
	, particleInterval(0.0f)
	, fadeManager(nullptr)
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
	//��ʌ��ʃN���X
	fadeManager = new FadeManager();
}

/// <summary>
/// �I������
/// </summary>
void ResultScene::Finalize()
{
	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		SafeDelete(fireWorksParticlePtr);
	}
}

/// <summary>
/// �ԉ΃p�[�e�B�N����o�^
/// </summary>
/// <param name="newFireWorksParticle"></param>
void ResultScene::EntryFireWorksParticle(FireWorksParticle* newFireWorksParticle)
{
	fireWorksParticle.emplace_back(newFireWorksParticle);
}

/// <summary>
/// �ԉ΃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteFireWorksParticle"></param>
void ResultScene::DeleteFireWorksParticle(FireWorksParticle* deleteFireWorksParticle)
{
	//�ԉ΂̃p�[�e�B�N���I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(fireWorksParticle.begin(), fireWorksParticle.end(), deleteFireWorksParticle);

	if (iter != fireWorksParticle.end())
	{
		//�ԉ΂̃p�[�e�B�N���I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, fireWorksParticle.end() - 1);
		fireWorksParticle.pop_back();

		return;
	}
}

/// <summary>
/// �ԉ΃p�[�e�B�N���̏o��
/// </summary>
void ResultScene::FireWorksParticlePop()
{
	if (!particleFlag)
	{
		//�p�[�e�B�N���̌����G���g���[����
		for (int i = 0; i < 500; i++)
		{
			FireWorksParticle* newFireWorksParticle = new FireWorksParticle({ 5000.0f,0.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle);
		}

		particleFlag = true;
	}
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Activate()
{
	frame = 0.0f;
	pUpdate = &ResultScene::UpdateGame;

	font = CreateFontToHandle("Oranienbaum", 150, 1);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Activate();
	}

	fadeManager->Activate();
}

/// <summary>
/// �V�[���؂�ւ�
/// </summary>
void ResultScene::SceneChange()
{
	if (CheckHitKey(KEY_INPUT_BACK))
	{
		pUpdate = &ResultScene::ReturnTitle;
	}
	if (CheckHitKey(KEY_INPUT_G))
	{
		pUpdate = &ResultScene::ReturnSelection;
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::UpdateGame(float deltaTime)
{
	FireWorksParticlePop();

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Update(deltaTime);
	}

	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;

		//5�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > 1.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}

	SceneChange();

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		//�p�[�e�B�N�����o���I�������
		if (fireWorksParticlePtr->IsParticleEnd())
		{
			DeleteFireWorksParticle(fireWorksParticlePtr);
		}
	}
}

/// <summary>
/// �^�C�g����ʂ�
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnTitle(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//�t���[������2.8�b�o�߂�����
	if (frame > 2.8f)
	{
		//�^�C�g����ʂ֑J��
		parent->SetNextScene(SceneManager::TITLE);
	}
}

/// <summary>
/// �Z���N�V������ʂ�
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnSelection(float deltaTime)
{
	frame += deltaTime;

	fadeManager->FadeMove();

	//�t���[������2.8�b�o�߂�����
	if (frame > 2.8f)
	{
		//�X�e�[�W�I����ʂ֑J��
		parent->SetNextScene(SceneManager::SELECTION);
	}
}

/// <summary>
/// ������x�v���C
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnStage(float deltaTime)
{
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Draw()
{
	//�X�e�[�W�N���A�Ȃ��
	if (Set::GetInstance().GetResult())
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameClear);

		for (auto fireWorksParticlePtr : fireWorksParticle)
		{
			fireWorksParticlePtr->Draw();
		}

	}
	//�Q�[���I�[�o�[�Ȃ��
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameOver);
	}

	fadeManager->Draw();

	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), font, "ParticleSize : %d", fireWorksParticle.size());
}