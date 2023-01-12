#include "SceneManager.h"
#include "PreCompiledHeader.h"
#include "TitleScene.h"
#include "StageSelection.h"
#include "PlayScene.h"
#include "Stage2.h"

SceneManager::SceneManager()
	: eachScene()
	, nowPointer(nullptr)
	, nowScene()
	, nextScene()
{
	//�����Ȃ�
}

SceneManager::~SceneManager()
{
	//�����Ȃ�
}

void SceneManager::Initialize()
{
	eachScene[TITLE] = new TitleScene(this);
	eachScene[SELECTION] = new StageSelection(this);
	eachScene[STAGE1] = new PlayScene(this);
	eachScene[STAGE2] = new Stage2(this);

	
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

void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScene[i]->Finalize();
		SafeDelete(eachScene[i]);
	}
}

void SceneManager::Update(float deltaTime)
{
	//���̃V�[�����Z�b�g����Ă����玟��
	if (nowScene != nextScene)
	{
		ChangeScene();						//���̃V�[��
	}

	if (nowPointer != nullptr)
	{
		nowPointer->Update(deltaTime);		//���̃V�[���̍X�V����
	}
}

void SceneManager::Draw()
{
	if (nowPointer != nullptr)
	{
		nowPointer->Draw();					//���̃V�[���̕`�揈��
	}
}

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