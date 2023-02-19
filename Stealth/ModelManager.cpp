#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH = "data/model/";    //modelフォルダまでのパス
const string ModelManager::PLAYER_PATH       = "player.mv1";     //playerモデルファイルのパス
const string ModelManager::ENEMY_PATH        = "enemy.mv1";      //enemyモデルファイルのパス
const string ModelManager::ENEMY_VISUAL_PATH = "enemyAngle.mv1"; //enemy_visualモデルファイルのパス
const string ModelManager::WALL_PATH         = "wall.mv1";       //wallモデルファイルのパス
const string ModelManager::CAKE_PATH         = "cake.mv1";       //cakeモデルファイルのパス
const string ModelManager::STAGE1_PATH       = "stage1.mv1";     //stage1モデルファイルのパス
const string ModelManager::STAGE2_PATH       = "stage2.mv1";     //stage2モデルファイルのパス
const string ModelManager::STAGE3_PATH       = "stage3.mv1";     //stage3モデルファイルのパス
const string ModelManager::STAGE4_PATH       = "stage4.mv1";     //stage4モデルファイルのパス
const string ModelManager::STAGE5_PATH       = "stage5.mv1";     //stage5モデルファイルのパス
const string ModelManager::GOAL_FLAG_PATH    = "goal.mv1";       //goal_flagモデルファイルのパス


/// <summary>
/// コンストラクタ
/// </summary>
ModelManager::ModelManager()
    : modelHandle()
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
    static ModelManager ModelManager;
    return ModelManager;
}

/// <summary>
/// 全てのモデルの読み込み
/// </summary>
void ModelManager::LoadAllModel()
{
    modelHandle[PLAYER]       = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, PLAYER_PATH).c_str());

    modelHandle[ENEMY]        = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, ENEMY_PATH).c_str());

    modelHandle[ENEMY_VISUAL] = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, ENEMY_VISUAL_PATH).c_str());

    modelHandle[WALL]         = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, WALL_PATH).c_str());

    modelHandle[CAKE]         = MV1LoadModel(InputPath(MODEL_FOLDER_PATH, CAKE_PATH).c_str());

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
            printfDx("モデルデータ読み込み失敗\n", i);
        }
    }
}

/// <summary>
/// モデルのパスを入力
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
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