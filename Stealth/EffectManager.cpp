#include "EffectManager.h"
#include "Effect.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager()
	: EFFECT_FOLDER_PATH("Data/Effect/")
	, REPOP_EFFECT_PATH("repop.efkefc")
	, REPOP_SIZE(30.0f)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectManager::~EffectManager()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		delete effect[i];
	}
}

/// <summary>
/// ����������
/// </summary>
void EffectManager::Initialize()
{
	//�e�G�t�F�N�g�̓ǂݍ���
	effect[REPOP] = new Effect(InputPath(EFFECT_FOLDER_PATH, REPOP_EFFECT_PATH), REPOP_SIZE);
}

/// <summary>
/// �`�揈��
/// </summary>
void EffectManager::Draw()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		effect[i]->Draw();
	}
}

/// <summary>
/// �G�t�F�N�g�̐���
/// </summary>
/// <param name="position">�G�t�F�N�g�̈ʒu</param>
/// <param name="effectType">�G�t�F�N�g�̎��</param>
void EffectManager::CreateEffect(VECTOR position, EffectType effectType)
{
	effect[effectType]->Update(position);
}

/// <summary>
/// �p�X�̓���
/// </summary>
/// <param name="folderPath">�G�t�F�N�g�t�H���_�[�̖��O</param>
/// <param name="effectPath">�G�t�F�N�g�̖��O</param>
/// <returns>�G�t�F�N�g�̃p�X</returns>
string EffectManager::InputPath(string folderPath, string effectPath)
{
	return string(folderPath + effectPath);
}