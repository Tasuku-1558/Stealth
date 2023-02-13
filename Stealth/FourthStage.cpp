#include "FourthStage.h"
#include "DxLib.h"

#include "SceneManager.h"
#include "PreCompiledHeader.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
FourthStage::FourthStage(SceneManager* const sceneManager)
	: SceneBase(sceneManager)
	, state()
	, pUpdate(nullptr)
	, font(0)
	, frame(0.0f)
	, particleFlag(false)
	, particleInterval(0.0f)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FourthStage::~FourthStage()
{
}

/// <summary>
/// ����������
/// </summary>
void FourthStage::Initialize()
{
}

/// <summary>
/// �I������
/// </summary>
void FourthStage::Finalize()
{
}

/// <summary>
/// ����������
/// </summary>
void FourthStage::Activate()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateStart(float deltaTime)
{
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateGame(float deltaTime)
{
}

/// <summary>
/// �S�[��
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateGoal(float deltaTime)
{
}

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
/// <param name="deltaTime"></param>
void FourthStage::UpdateOver(float deltaTime)
{
}

/// <summary>
/// �`�揈��
/// </summary>
void FourthStage::Draw()
{
}