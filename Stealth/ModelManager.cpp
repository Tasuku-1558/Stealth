#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH ="data/model/";      //modelフォルダまでのパス
const string ModelManager::PLAYER_BODY_PATH  = "player_body.mv1"; //player_bodyモデルファイルのパス
const string ModelManager::PLAYER_ARM_PATH   = "arm.mv1";         //player_armモデルファイルのパス
const string ModelManager::ENEMY_BODY_PATH   = "enemy_body.mv1";  //enemy_bodyモデルファイルのパス
const string ModelManager::BOAL_PATH         = "boal.mv1";        //boalモデルファイルのパス
const string ModelManager::STAGE1_PATH       = "stage1.mv1";      //stage1モデルファイルのパス


ModelManager::ModelManager()
    : modelHandle()
{
    LoadAllModel();
}

ModelManager::~ModelManager()
{
    DeleteAllModel();
}

ModelManager& ModelManager::GetInstance()
{
    static ModelManager ModelManager;
    return ModelManager;
}

void ModelManager::LoadAllModel()
{
    //モデルファイルのパス
    string failePath = MODEL_FOLDER_PATH + PLAYER_BODY_PATH;
    modelHandle[PLAYER_BODY] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + PLAYER_ARM_PATH;
    modelHandle[PLAYER_ARM] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + ENEMY_BODY_PATH;
    modelHandle[ENEMY_BODY] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + BOAL_PATH;
    modelHandle[BOAL] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + STAGE1_PATH;
    modelHandle[STAGE1] = MV1LoadModel(failePath.c_str());

    //読み込み失敗ならエラー
    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        if (modelHandle[i] < 0)
        {
            printfDx("モデルデータ読み込み失敗\n", i);
        }
    }
}

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

const int& ModelManager::GetModelHandle(ModelType modelType) const
{
    if (modelType == MODEL_AMOUNT)
    {
        printfDx("不正な値を参照しています");
        return modelHandle[0];
    }

    return modelHandle[modelType];
}