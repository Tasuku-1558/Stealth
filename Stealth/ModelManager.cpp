#include "ModelManager.h"
#include "DxLib.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
ModelManager::~ModelManager()
{
    DeleteAllModel();
}

/// <summary>
/// �A�h���X��Ԃ�
/// </summary>
/// <returns>modelManager��Ԃ�</returns>
ModelManager& ModelManager::GetInstance()
{
    static ModelManager modelManager;
    return modelManager;
}

/// <summary>
/// �S�Ẵ��f���̓ǂݍ���
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

        //�ǂݍ��ݎ��s�Ȃ�G���[
        if (modelHandle[i] < 0)
        {
            printfDx("���f���f�[�^�ǂݍ��ݎ��s[%d]\n", i);
        }
    }
}

/// <summary>
/// �S�Ẵ��f���̍폜
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
/// ���f���n���h���̎Q�Ƃ�Ԃ�
/// </summary>
/// <param name="modelType">���f���̎��</param>
/// <returns>���f���n���h����Ԃ�</returns>
const int& ModelManager::GetModelHandle(ModelType modelType) const
{
    if (modelType == MODEL_AMOUNT)
    {
        printfDx("�s���Ȓl���Q�Ƃ��Ă��܂�");
        return modelHandle[0];
    }

    return modelHandle[modelType];
}