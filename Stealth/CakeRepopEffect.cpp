#include "CakeRepopEffect.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"


const string CakeRepopEffect::EFFECT_FOLDER_PATH = "data/effect/";		//effect�t�H���_�܂ł̃p�X
const string CakeRepopEffect::CAKE_PATH			 = "ball.efkefc";		//�P�[�L�ăX�|�[�����G�t�F�N�g�̃p�X

/// <summary>
/// �R���X�g���N�^
/// </summary>
CakeRepopEffect::CakeRepopEffect() : EffectBase()
	, effectHandle(0)
	, effectPos_X(0.0f)
	, effectPos_Y(0.0f)
	, effectPos_Z(0.0f)
	, effectTime(0)
	, playingEffectHandle(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CakeRepopEffect::~CakeRepopEffect()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void CakeRepopEffect::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + CAKE_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 30.0f);
}

/// <summary>
/// �I������
/// </summary>
void CakeRepopEffect::Finalize()
{
	//�G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// ����������
/// </summary>
void CakeRepopEffect::Activate()
{
	//�G�t�F�N�g���~����
	StopEffekseer3DEffect(playingEffectHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="ballPosX"></param>
/// <param name="ballPosY"></param>
/// <param name="ballPosZ"></param>
void CakeRepopEffect::Update(float ballPosX, float ballPosY, float ballPosZ)
{
	//�G�t�F�N�g�̈ʒu�ݒ�
	effectPos_X = ballPosX;
	effectPos_Y = ballPosY;
	effectPos_Z = ballPosZ;

	//����I�ɃG�t�F�N�g���Đ�
	if (effectTime % 1 == 0)
	{
		//�G�t�F�N�g���Đ�
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	//�Đ����̃G�t�F�N�g���ړ�
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, effectPos_X, effectPos_Y, effectPos_Z);

	//���Ԃ��o��
	effectTime++;
}

/// <summary>
/// �`�揈��
/// </summary>
void CakeRepopEffect::Draw()
{
	//�Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	//�Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}