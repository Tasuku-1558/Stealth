#include "Effect.h"
#include "EffekseerForDXLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="effectPath">�G�t�F�N�g�̃p�X</param>
/// <param name="effectSize">�G�t�F�N�g�̃T�C�Y</param>
Effect::Effect(string effectPath, float effectSize)
{
	effectHandle = LoadEffekseerEffect(effectPath.c_str(), effectSize);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Effect::~Effect()
{
	//�G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="position">�G�t�F�N�g�̈ʒu</param>
void Effect::Update(VECTOR position)
{
	//���Ԃ��o��
	effectTime++;

	//�G�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		//�G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		effectTime = 0;
	}

	//�Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
}

/// <summary>
/// �`�揈��
/// </summary>
void Effect::Draw()
{
	//�Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	//�Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}