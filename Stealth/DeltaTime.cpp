#include "DeltaTime.h"
#include "DxLib.h"


float DeltaTime::deltaTime = 0.0f;
float DeltaTime::prevTime  = 0.0f;
float DeltaTime::nowTime   = 0.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
DeltaTime::DeltaTime()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DeltaTime::~DeltaTime()
{
	//�����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void DeltaTime::Initialize()
{
	// ���Ԍv��
	prevTime = nowTime = GetNowCount();
}

void DeltaTime::DeltaTimeCount()
{
	// �t���[�����Ԃ��Z�o
	nowTime = GetNowCount();

	deltaTime = (nowTime - prevTime) / 1000.0f;

	prevTime = nowTime;
}