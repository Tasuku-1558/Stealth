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
///// コンストラクタ
///// </summary>
//SelectionKey::SelectionKey(SceneManager* const sceneManager)
//{
//}
//
///// <summary>
///// デストラクタ
///// </summary>
//SelectionKey::~SelectionKey()
//{
//}
//
///// <summary>
///// 初期化処理
///// </summary>
//void SelectionKey::Initialize()
//{
//	stageMax = sizeof(stageName) / sizeof(char[32]);
//}
//
///// <summary>
///// 終了処理
///// </summary>
//void SelectionKey::Finalize()
//{
//}
//
///// <summary>
///// 活性化処理
///// </summary>
//void SelectionKey::Activate()
//{
//	stageNo = 1;
//	changeScene = false;
//	changeTimeCount = 0;
//}
//
///// <summary>
///// キー操作
///// </summary>
//void SelectionKey::KeyMove()
//{
//	//キー操作
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
//	//リターンキーを押したならば
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
///// 選択ステージを1個前に持っていく
///// </summary>
///// <param name="stageNum"></param>
///// <returns></returns>
//int SelectionKey::stageDecrement(int stageNumber)
//{
//	//最初のステージに来た時
//	if (stageNumber == 1)
//	{
//		return stageMax;
//	}
//
//	return stageNumber - 1;
//}
//
///// <summary>
///// 選択ステージを1個先に持っていく
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
//	//各シーン
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
///// 描画処理
///// </summary>
//void SelectionKey::Draw()
//{
//}