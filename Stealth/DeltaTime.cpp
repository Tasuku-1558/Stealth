#include "DeltaTime.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
DeltaTime::DeltaTime()
	//: deltaTime(0.0f)
	//, waitFrameTime(0.0f)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DeltaTime::~DeltaTime()
{
	//�����Ȃ�
}

/// <summary>
/// �A�h���X��Ԃ�
/// </summary>
/// <returns></returns>
DeltaTime& DeltaTime::GetInstance()
{
	static DeltaTime deltaTime;
	return deltaTime;
}

/// <summary>
/// ����������
/// </summary>
void DeltaTime::Initialize()
{
	//���Ԍv��
	//prevTime = nowTime = GetNowHiPerformanceCount();

	////�ҋ@�t���[������(60fps)
	//waitFrameTime = 16667.0f;
}

/// <summary>
/// 60Fps�v��
/// </summary>
void DeltaTime::DeltaTimeCount()
{
	//���݂̃t���[�����X�V
	//nowTime = GetNowHiPerformanceCount();

	//deltaTime = (nowTime - prevTime) / 1000000.0f;

	////60fps����p���[�v
	//while (GetNowHiPerformanceCount() - nowTime < waitFrameTime);

	////���݂̃t���[����ۑ�
	//prevTime = nowTime;
}