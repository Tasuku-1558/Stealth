#include "EffectManager.h"
#include "Effect.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EffectManager::EffectManager()
	: EFFECT_FOLDER_PATH("Data/Effect/")
	, RESPAWN_EFFECT_PATH("Respawn/Respawn.efkefc")
	, SHOT_EFFECT_PATH("Shot/Shot.efkefc")
	, RESPAWN_SIZE(30.0f)
	, SHOT_SIZE(50.0f)
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectManager::~EffectManager()
{
	DeleteEffect();
}

/// <summary>
/// ����������
/// </summary>
void EffectManager::Initialize()
{
	Effects effects[] =
	{
		{RESPAWN_EFFECT_PATH, RESPAWN_SIZE},
		{SHOT_EFFECT_PATH,	  SHOT_SIZE},
	};

	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		//�e�G�t�F�N�g�̓ǂݍ���
		effect[i] = new Effect(Input::InputPath(EFFECT_FOLDER_PATH, effects[i].effectPath), effects[i].effectSize);
	}
}

/// <summary>
/// �G�t�F�N�g�̍폜
/// </summary>
void EffectManager::DeleteEffect()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		if (effect[i] != NULL)
		{
			delete effect[i];
			effect[i] = NULL;
		}
	}
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