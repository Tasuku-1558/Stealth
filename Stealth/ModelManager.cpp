#include "ModelManager.h"
#include "DxLib.h"


const string ModelManager::MODEL_FOLDER_PATH = "data/model/";   //model�t�H���_�܂ł̃p�X
const string ModelManager::PLAYER_PATH       = "player.mv1";    //player���f���t�@�C���̃p�X
const string ModelManager::ENEMY_PATH        = "enemy.mv1";     //enemy���f���t�@�C���̃p�X
const string ModelManager::WALL_PATH         = "wall.mv1";      //wall���f���t�@�C���̃p�X
const string ModelManager::BALL_PATH         = "ball.mv1";      //ball���f���t�@�C���̃p�X
const string ModelManager::STAGE1_PATH       = "stage1.mv1";    //stage1���f���t�@�C���̃p�X
const string ModelManager::STAGE2_PATH       = "stage2.mv1";    //stage1���f���t�@�C���̃p�X


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
    string failePath = MODEL_FOLDER_PATH + PLAYER_PATH;
    modelHandle[PLAYER] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + ENEMY_PATH;
    modelHandle[ENEMY] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + WALL_PATH;
    modelHandle[WALL] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + BALL_PATH;
    modelHandle[BALL] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + STAGE1_PATH;
    modelHandle[STAGE1] = MV1LoadModel(failePath.c_str());

    failePath = MODEL_FOLDER_PATH + STAGE2_PATH;
    modelHandle[STAGE2] = MV1LoadModel(failePath.c_str());

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