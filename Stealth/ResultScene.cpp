#include "ResultScene.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "FireWorksParticle.h"
#include "BackGround.h"
#include "FadeManager.h"
#include "Set.h"


char GameClear[] = { "GAME CLEAR" };
char GameOver[]  = { "GAME OVER" };

const string ResultScene::IMAGE_FOLDER_PATH = "data/image/";		//image�t�H���_�܂ł̃p�X
const string ResultScene::RESULT_UI_PATH	= "resultUi.png";		//���U���g��ʂ�UI�̃p�X


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
ResultScene::ResultScene(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, font(0)
	, frame(0.0f)
	, fireWorksParticle()
	, backGround(nullptr)
	, particleFlag(false)
	, particleInterval(0.0f)
	, fadeManager(nullptr)
	, stageNo(0)
	, clear(false)
	, resultUiImage(0)
	, alpha(0)
	, inc(0)
	, prevAlpha(0)
	, title(false)
	, selection(false)
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
	//�w�i�N���X
	backGround = new BackGround();
	backGround->Initialize();

	//��ʌ��ʃN���X
	fadeManager = new FadeManager();

	resultUiImage = LoadGraph(InputPath(IMAGE_FOLDER_PATH, RESULT_UI_PATH).c_str());

	alpha = 255;
	inc = -3;
}

string ResultScene::InputPath(string folderPath, string path)
{
	return string(folderPath + path);
}

/// <summary>
/// �I������
/// </summary>
void ResultScene::Finalize()
{
	SafeDelete(backGround);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(font);

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		SafeDelete(fireWorksParticlePtr);
	}

	DeleteGraph(resultUiImage);
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
			FireWorksParticle* newFireWorksParticle = new FireWorksParticle({ 500.0f,600.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle);

			FireWorksParticle* newFireWorksParticle2 = new FireWorksParticle({ 1500.0f,600.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle2);

			FireWorksParticle* newFireWorksParticle3 = new FireWorksParticle({ 1000.0f,800.0f,0.0f });
			EntryFireWorksParticle(newFireWorksParticle3);
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
	stageNo = Set::GetInstance().GetStage();

	clear = Set::GetInstance().GetResult();

	title = false;
	selection = false;

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
		title = true;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		selection = true;
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::Update(float deltaTime)
{
	FireWorksParticlePop();
	
	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;
	
		//5�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > 2.0f)
		{
			particleFlag = false;
			particleInterval = 0.0f;
		}
	}
	
	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Update(deltaTime);
	}
	
	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		//�p�[�e�B�N�����o���I�������
		if (fireWorksParticlePtr->IsParticleEnd())
		{
			DeleteFireWorksParticle(fireWorksParticlePtr);
		}
	}
	
	SceneChange();

	ReturnTitle(deltaTime);
	ReturnSelection(deltaTime);
}

/// <summary>
/// �^�C�g����ʂ�
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnTitle(float deltaTime)
{
	if (title)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//�t���[������2.4�b�o�߂�����
		if (frame > 2.4f)
		{
			//�^�C�g����ʂ֑J��
			parent->SetNextScene(SceneManager::TITLE);
		}
	}
}

/// <summary>
/// �Z���N�V������ʂ�
/// </summary>
/// <param name="deltaTime"></param>
void ResultScene::ReturnSelection(float deltaTime)
{
	if (selection)
	{
		frame += deltaTime;

		fadeManager->FadeMove();

		//�t���[������2.4�b�o�߂�����
		if (frame > 2.4f)
		{
			//�X�e�[�W�I����ʂ֑J��
			parent->SetNextScene(SceneManager::SELECTION);
		}
	}
}

void ResultScene::Blink()
{
	if (alpha > 255 && inc > 0)
	{
		inc *= -1;
	}

	if (alpha < 0 && inc < 0)
	{
		inc *= -1;
	}

	alpha += inc;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	DrawRotaGraph(1500, 1000, 0.5f, 0, resultUiImage, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Draw()
{
	//�w�i�`��
	//backGround->Draw();

	//�X�e�[�W�N���A�Ȃ��
	if (clear)
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 215, 0), font, "%s", GameClear);

	}
	//�Q�[���I�[�o�[�Ȃ��
	else
	{
		DrawFormatStringToHandle(600, 400, GetColor(255, 0, 0), font, "%s", GameOver);
	}

	for (auto fireWorksParticlePtr : fireWorksParticle)
	{
		fireWorksParticlePtr->Draw();
	}

	Blink();

	fadeManager->Draw();
}