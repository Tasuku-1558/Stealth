#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH="data/model/";     //model�t�H���_�܂ł̃p�X
const string ModelManager::PLAYER_BODY_PATH = "body.mv1";       //player_body���f���t�@�C���̃p�X
const string ModelManager::PLAYER_ARM_PATH = "arm.mv1";         //player_arm���f���t�@�C���̃p�X

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
    //���f���t�@�C���̃p�X
    string FailePath = MODEL_FOLDER_PATH + PLAYER_BODY_PATH;
    modelHandle[PLAYER_BODY] = MV1LoadModel(FailePath.c_str());

    FailePath = MODEL_FOLDER_PATH + PLAYER_ARM_PATH;
    modelHandle[PLAYER_ARM] = MV1LoadModel(FailePath.c_str());


    //�ǂݍ��ݎ��s�Ȃ�G���[
    for (int i = 0; i < MODEL_AMOUNT; ++i)
    {
        if (modelHandle[i] < 0)
        {
            printfDx("���f���f�[�^�ǂݍ��ݎ��s\n", i);
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
        printfDx("�s���Ȓl���Q�Ƃ��Ă��܂�");
        return modelHandle[0];
    }

    return modelHandle[modelType];
}