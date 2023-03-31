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
	effect[0] = new Effect(InputPath(EFFECT_FOLDER_PATH, REPOP_EFFECT_PATH), REPOP_SIZE);
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
/// <param name="number">�G�t�F�N�g�̎��</param>
/// <param name="position">�G�t�F�N�g�̈ʒu</param>
void EffectManager::CreateEffect(int number, VECTOR position)
{
	effect[number]->Update(position);
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