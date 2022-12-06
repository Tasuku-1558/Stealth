#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH="data/model/";     //modelフォルダまでのパス
const string ModelManager::PLAYER_BODY_PATH = "body.mv1";       //player_bodyモデルファイルのパス
const string ModelManager::PLAYER_ARM_PATH = "arm.mv1";         //player_armモデルファイルのパス

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
    string FailePath = MODEL_FOLDER_PATH + PLAYER_BODY_PATH;
    modelHandle[PLAYER_BODY] = MV1LoadModel(FailePath.c_str());

    FailePath = MODEL_FOLDER_PATH + PLAYER_ARM_PATH;
    modelHandle[PLAYER_ARM] = MV1LoadModel(FailePath.c_str());


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