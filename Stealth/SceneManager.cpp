#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "TitleScene.h"
#include "StageSelection.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
	: eachScene()
	, nowPointer(nullptr)
	, nowScene()
	, nextScene()
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::Initialize()
{
	//�e�V�[����o�^
	eachScene[TITLE]	 = new TitleScene(this);
	eachScene[SELECTION] = new StageSelection(this);
	eachScene[STAGE1]	 = new FirstStage(this);
	eachScene[STAGE2]	 = new SecondStage(this);
	eachScene[STAGE3]	 = new ThirdStage(this);

	
	//�S�ẴV�[���̏�����
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Initialize();
	}

	//�ŏ��̃V�[���̏������Ɗ�����
	nowScene = nextScene = TITLE;

	nowPointer = eachScene[nowScene];
	nowPointer->Activate();
}

/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Finalize();
		SafeDelete(eachScene[i]);
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void SceneManager::Update(float deltaTime)
{
	//���̃V�[�����Z�b�g����Ă����玟��
	if (nowScene != nextScene)
	{
		ChangeScene();						//���̃V�[����
	}

	if (nowPointer != nullptr)
	{
		nowPointer->Update(deltaTime);		//���̃V�[���̍X�V����
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Draw()
{
	if (nowPointer != nullptr)
	{
		nowPointer->Draw();					//���̃V�[���̕`�揈��
	}
}

/// <summary>
/// ���̃V�[�����Z�b�g
/// </summary>
/// <param name="next"></param>
void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

void SceneManager::ChangeScene()
{
	if (nextScene == END)
	{
		return;
	}

	nowPointer = eachScene[nextScene];	//���̃V�[����
	nowScene = nextScene;
	nowPointer->Activate();				//���̃V�[����������
}

/// <summary>
/// ���̃V�[�����擾
/// </summary>
/// <returns></returns>
SceneManager::Scene SceneManager::GetNowScene()
{
	return nowScene;
}

/// <summary>
/// ���̃V�[�����擾
/// </summary>
/// <returns></returns>
SceneManager::Scene SceneManager::GetNextScene()
{
	return nextScene;
}