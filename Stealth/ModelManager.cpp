#include "ModelManager.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
ModelManager::ModelManager()
    : modelHandle()
    , MODEL_FOLDER_PATH("Data/Model/")
    , PLAYER_PATH("Player/player.mv1")
    , ENEMY_PATH("Enemy/enemy.mv1")
    , ENEMY_VISUAL_PATH("Enemy/enemyAngle.mv1")
    , CAKE_PATH("Cake/cake.mv1")
    , CAKE_HALF_PATH("Cake/cakeHalf.mv1")
    , STONE_PATH("Stone/stone.mv1")
    , STAGE_PATH("Stage/stage.mv1")
    , GOAL_FLAG_PATH("Goal/goal.mv1")
{
    LoadAllModel();
}

/// <summary>
/// デストラクタ
/// </summary>
ModelManager::~ModelManager()
{
    DeleteAllModel();
}

/// <summary>
/// アドレスを返す
/// </summary>
/// <returns>modelManagerを返す</returns>
ModelManager& ModelManager::GetInstance()
{
    static ModelManager modelManager;
    return modelManager;
}

/// <summary>
/// 全てのモデルの読み込み
/// </summary>
void ModelManager::LoadAllModel()
{
    Model model[] =
    {
        {PLAYER_PATH},
        {ENEMY_PATH},
        {ENEMY_VISUAL_PATH},
        {CAKE_PATH},
        {CAKE_HALF_PATH},
        {STONE_PATH},
        {STAGE_PATH},
        {GOAL_FLAG_PATH},
    };

    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        modelHandle[i] = MV1LoadModel(Input::InputPath(MODEL_FOLDER_PATH, model[i].modelPath).c_str());

        //読み込み失敗ならエラー
        if (modelHandle[i] < 0)
        {
            printfDx("モデルデータ読み込み失敗[%d]\n", i);
        }
    }
}

/// <summary>
/// 全てのモデルの削除
/// </summary>
void ModelManager::DeleteAllModel()
{
    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        if (modelHandle[i] != NULL)
        {
            MV1DeleteModel(modelHandle[i]);
            modelHandle[i] = NULL;
        }
    }
}

/// <summary>
/// モデルハンドルの参照を返す
/// </summary>
/// <param name="modelType">モデルの種類</param>
/// <returns>モデルハンドルを返す</returns>
const int& ModelManager::GetModelHandle(ModelType modelType) const
{
    if (modelType == MODEL_AMOUNT)
    {
        printfDx("不正な値を参照しています");
        return modelHandle[0];
    }

    return modelHandle[modelType];
}