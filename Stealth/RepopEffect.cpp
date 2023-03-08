#include "RepopEffect.h"
#include "EffekseerForDXLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
RepopEffect::RepopEffect(/*string effectPath, float effectSize*/)
	: EffectBase()
	, EFFECT_FOLDER_PATH("Data/effect/")
	, CAKE_PATH("cake.efkefc")
	, MAGNIFICATION(30.0f)
{
	string failePath = EFFECT_FOLDER_PATH + CAKE_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), MAGNIFICATION);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RepopEffect::~RepopEffect()
{
	//�G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="pos"></param>
void RepopEffect::Update(VECTOR pos)
{
	//����I�ɃG�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		//�G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	//�Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x, pos.y, pos.z);

	//���Ԃ��o��
	effectTime++;
}

/// <summary>
/// �`�揈��
/// </summary>
void RepopEffect::Draw()
{
	//�Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	//�Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}