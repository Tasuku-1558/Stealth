#include "ModelManager.h"
#include "DxLib.h"


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
    , STAGE1_PATH("Stage/stage1.mv1")
    , STAGE2_PATH("Stage/stage2.mv1")
    , STAGE3_PATH("Stage/stage3.mv1")
    , STAGE4_PATH("Stage/stage4.mv1")
    , STAGE5_PATH("Stage/stage5.mv1")
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
/// <returns></returns>
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
    modelHandle[PLAYER]       = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, PLAYER_PATH).c_str());

    modelHandle[ENEMY]        = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, ENEMY_PATH).c_str());

    modelHandle[ENEMY_VISUAL] = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, ENEMY_VISUAL_PATH).c_str());

    modelHandle[CAKE]         = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, CAKE_PATH).c_str());

    modelHandle[CAKE_HALF]    = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, CAKE_HALF_PATH).c_str());

    modelHandle[STONE]        = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, STONE_PATH).c_str());

    modelHandle[STAGE1]       = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, STAGE1_PATH).c_str());

    modelHandle[STAGE2]       = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, STAGE2_PATH).c_str());

    modelHandle[STAGE3]       = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, STAGE3_PATH).c_str());

    modelHandle[STAGE4]       = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, STAGE4_PATH).c_str());

    modelHandle[STAGE5]       = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, STAGE5_PATH).c_str());

    modelHandle[GOAL]         = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, GOAL_FLAG_PATH).c_str());


    //読み込み失敗ならエラー
    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        if (modelHandle[i] < 0)
        {
            printfDx("モデルデータ読み込み失敗[%d]\n", i);
        }
    }
}

/// <summary>
/// モデルのパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="modelPath"></param>
/// <returns></returns>
string ModelManager::InputPath(string folderPath, string modelPath)
{
    return string(folderPath + modelPath);
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
/// <param name="modelType"></param>
/// <returns></returns>
const int& ModelManager::GetModelHandle(ModelType modelType) const
{
    if (modelType == MODEL_AMOUNT)
    {
        printfDx("不正な値を参照しています");
        return modelHandle[0];
    }

    return modelHandle[modelType];
}