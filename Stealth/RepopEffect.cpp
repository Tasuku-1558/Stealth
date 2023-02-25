#include "RepopEffect.h"
#include "EffekseerForDXLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
RepopEffect::RepopEffect() : EffectBase()
	, effectHandle(0)
	, effectTime(0)
	, playingEffectHandle(0)
	, EFFECT_FOLDER_PATH("data/effect/")
	, CAKE_PATH("cake.efkefc")
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RepopEffect::~RepopEffect()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void RepopEffect::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + CAKE_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 30.0f);
}

/// <summary>
/// �I������
/// </summary>
void RepopEffect::Finalize()
{
	//�G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// ����������
/// </summary>
void RepopEffect::Activate()
{
	//�G�t�F�N�g���~����
	StopEffekseer3DEffect(playingEffectHandle);
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