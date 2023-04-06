#include "EffectManager.h"
#include "Effect.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager()
	: EFFECT_FOLDER_PATH("Data/Effect/")
	, RESPAWN_EFFECT_PATH("Respawn/Respawn.efkefc")
	, RESPAWN_SIZE(30.0f)
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
	effect[RESPAWN] = new Effect(Input::InputPath(EFFECT_FOLDER_PATH, RESPAWN_EFFECT_PATH), RESPAWN_SIZE);
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