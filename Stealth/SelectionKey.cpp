//#include "SelectionKey.h"
//#include "DxLib.h"
//
//
//char stageName[][32] =
//{
//	"STAGE1",
//	"STAGE2",
//	"TITLE",
//};
//
///// <summary>
///// �R���X�g���N�^
///// </summary>
//SelectionKey::SelectionKey(SceneManager* const sceneManager)
//{
//}
//
///// <summary>
///// �f�X�g���N�^
///// </summary>
//SelectionKey::~SelectionKey()
//{
//}
//
///// <summary>
///// ����������
///// </summary>
//void SelectionKey::Initialize()
//{
//	stageMax = sizeof(stageName) / sizeof(char[32]);
//}
//
///// <summary>
///// �I������
///// </summary>
//void SelectionKey::Finalize()
//{
//}
//
///// <summary>
///// ����������
///// </summary>
//void SelectionKey::Activate()
//{
//	stageNo = 1;
//	changeScene = false;
//	changeTimeCount = 0;
//}
//
///// <summary>
///// �L�[����
///// </summary>
//void SelectionKey::KeyMove()
//{
//	//�L�[����
//	if (CheckHitKey(KEY_INPUT_UP))
//	{
//		stageNo = stageDecrement(stageNo);
//	}
//	if (CheckHitKey(KEY_INPUT_DOWN))
//	{
//		stageNo = stageIncrement(stageNo);
//	}
//	if (CheckHitKey(KEY_INPUT_BACK))
//	{
//		parent->SetNextScene(SceneManager::TITLE);
//	}
//	if (CheckHitKey(KEY_INPUT_RETURN))
//	{
//		changeScene = true;
//	}
//
//	//���^�[���L�[���������Ȃ��
//	if (changeScene)
//	{
//		changeTimeCount++;
//
//		if (changeTimeCount > maxTime)
//		{
//			StageCreator(stageNo);
//		}
//	}
//}
//
///// <summary>
///// �I���X�e�[�W��1�O�Ɏ����Ă���
///// </summary>
///// <param name="stageNum"></param>
///// <returns></returns>
//int SelectionKey::stageDecrement(int stageNumber)
//{
//	//�ŏ��̃X�e�[�W�ɗ�����
//	if (stageNumber == 1)
//	{
//		return stageMax;
//	}
//
//	return stageNumber - 1;
//}
//
///// <summary>
///// �I���X�e�[�W��1��Ɏ����Ă���
///// </summary>
///// <param name="stageNum"></param>
///// <returns></returns>
//int SelectionKey::stageIncrement(int stageNumber)
//{
//	if (stageNumber > 0 && stageNumber < stageMax)
//	{
//		return stageNumber + 1;
//	}
//
//	return 1;
//}
//
//int SelectionKey::StageCreator(int stageNumber)
//{
//	if (stageNumber < 0)
//	{
//		return NULL;
//	}
//
//	//�e�V�[��
//	switch (stageNumber)
//	{
//	case 1:
//		parent->SetNextScene(SceneManager::STAGE1);
//		break;
//
//	case 2:
//		parent->SetNextScene(SceneManager::STAGE2);
//		break;
//
//	case 3:
//		parent->SetNextScene(SceneManager::TITLE);
//		break;
//	}
//
//	return NULL;
//}
//
///// <summary>
///// �`�揈��
///// </summary>
//void SelectionKey::Draw()
//{
//}