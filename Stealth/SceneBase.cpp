#include "SceneBase.h"
#include "TitleScene.h"
#include "StageSelection.h"
#include "FirstStage.h"
#include "ResultScene.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneType"></param>
SceneBase::SceneBase(SceneType sceneType)
	: nowSceneType(sceneType)
	, number(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
	//�����Ȃ�
}

/// <summary>
/// �V�����V�[���𐶐�����
/// </summary>
/// <param name="nowScene">���݂̃V�[��</param>
/// <returns>���̃V�[��</returns>
SceneBase* SceneBase::CreateScene(SceneType nowScene)
{
	SceneBase* retScene = nullptr;
	StageSelection* stageSelection = nullptr;
	FirstStage* firstStage = nullptr;

	switch (nowScene)
	{
	case SceneType::TITLE:
		retScene = new TitleScene();
		break;

	case SceneType::SELECTION:
		stageSelection = new StageSelection();
		number = stageSelection->GetStage();
		retScene = stageSelection;
		break;

	case SceneType::PLAY:
		firstStage = new FirstStage();
		firstStage->stage(number);
		retScene = firstStage;
		break;

	case SceneType::RESULT:
		retScene = new ResultScene();
		break;
	}

	return retScene;
}