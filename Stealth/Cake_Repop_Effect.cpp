#include "Cake_Repop_Effect.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"


const string Cake_Repop_Effect::EFFECT_FOLDER_PATH = "data/effect/";		//effect�t�H���_�܂ł̃p�X
const string Cake_Repop_Effect::CAKE_PATH			= "ball.efkefc";		//�P�[�L�ăX�|�[�����G�t�F�N�g�̃p�X

/// <summary>
/// �R���X�g���N�^
/// </summary>
Cake_Repop_Effect::Cake_Repop_Effect() : EffectBase()
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
Cake_Repop_Effect::~Cake_Repop_Effect()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Cake_Repop_Effect::Initialize()
{
	string failePath = EFFECT_FOLDER_PATH + CAKE_PATH;
	effectHandle = LoadEffekseerEffect(failePath.c_str(), 30.0f);
}

/// <summary>
/// �I������
/// </summary>
void Cake_Repop_Effect::Finalize()
{
	//�G�t�F�N�g���\�[�X���폜
	DeleteEffekseerEffect(effectHandle);
}

/// <summary>
/// ����������
/// </summary>
void Cake_Repop_Effect::Activate()
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
void Cake_Repop_Effect::Update(float ballPosX, float ballPosY, float ballPosZ)
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
void Cake_Repop_Effect::Draw()
{
	//�Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	//�Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();
}