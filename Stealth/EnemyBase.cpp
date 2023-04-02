#include "EnemyBase.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBase::EnemyBase()
	: markImage(0)
	, visualModelHandle(0)
	, speed(0.0f)
	, changeSpeed(0.0f)
	, length(900.0f)
	, bulletDirection(0.0f)
	, playerSpotted(false)
	, cakeFlag(false)
	, targetPosition()
	, visualPosition()
	, visualDir()
	, RANGE_DEGREE(27.0f)
	, RADIUS(100.0f)
{
	//�G�l�~�[�̍s���p�^�[�����X�g
	MapList();
	MapList2();
	MapList3();
	MapList4();
	MapList5();
	MapList6();
	MapList7();
	MapList8();
	MapList9();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBase::~EnemyBase()
{
	//�����Ȃ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g(���E�ړ��̓G)
/// FirstStage�̓G
/// </summary>
void EnemyBase::MapList()
{
	positionList[0].push_back({ 1000.0f, 0.0f, 2900.0f });
	positionList[0].push_back({ -1000.0f, 0.0f, 2900.0f });

	itr[0] = positionList[0].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g2(�ǂ̎�������G)
/// SecondStage�̓G
/// </summary>
void EnemyBase::MapList2()
{
	positionList[1].push_back({ -2200.0f, 0.0f, 600.0f });
	positionList[1].push_back({ -2200.0f, 0.0f, -700.0f });
	positionList[1].push_back({ -1400.0f, 0.0f, -700.0f });
	positionList[1].push_back({ -1400.0f, 0.0f, 600.0f });

	itr[1] = positionList[1].begin();	//�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g3(�㉺�ړ��̓G)
/// SecondStage�̓G
/// </summary>
void EnemyBase::MapList3()
{
	positionList[2].push_back({ -5000.0f, 0.0f, 0.0f });
	positionList[2].push_back({ -4400.0f, 0.0f, 0.0f });

	itr[2] = positionList[2].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g4(�㉺�ړ��̓G)
/// ThirdStage�̓G
/// </summary>
void EnemyBase::MapList4()
{
	positionList[3].push_back({ -2500.0f, 0.0f, 800.0f });
	positionList[3].push_back({ -1500.0f, 0.0f, 800.0f });

	itr[3] = positionList[3].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g5(�S�[���̈ʒu���ǂ��G)
/// ThirdStage�̓G
/// </summary>
void EnemyBase::MapList5()
{
	positionList[4].push_back({ -2500.0f, 0.0f,  5000.0f });
	positionList[4].push_back({ -2500.0f, 0.0f,  4300.0f });
	positionList[4].push_back({ -2800.0f, 0.0f,  4300.0f });
	positionList[4].push_back({ -2500.0f, 0.0f,  4300.0f });

	itr[4] = positionList[4].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g6(���E�ړ��̓G)
/// FourthStage�̓G
/// </summary>
void EnemyBase::MapList6()
{
	positionList[5].push_back({ -1300.0f, 0.0f, 500.0f });
	positionList[5].push_back({ -1300.0f, 0.0f, -700.0f });

	itr[5] = positionList[5].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g7(�ǂ̎�������G)
/// FourthStage�̓G
/// </summary>
void EnemyBase::MapList7()
{
	positionList[6].push_back({ -4800.0f, 0.0f, -500.0f });
	positionList[6].push_back({ -4800.0f, 0.0f, -1500.0f });
	positionList[6].push_back({ -3800.0f, 0.0f, -1500.0f });
	positionList[6].push_back({ -3800.0f, 0.0f, -500.0f });

	itr[6] = positionList[6].begin();	//�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g8(�E��L���ړ��̓G)
/// FifthStage�̓G
/// </summary>
void EnemyBase::MapList8()
{
	positionList[7].push_back({ -2300.0f, 0.0f, 3300.0f });
	positionList[7].push_back({ -620.0f, 0.0f, 3300.0f });
	positionList[7].push_back({ -620.0f, 0.0f, 2800.0f });
	positionList[7].push_back({ -620.0f, 0.0f, 3300.0f });

	itr[7] = positionList[7].begin();   //�C�e���[�^��擪�ɐݒ�
}

/// <summary>
/// �G�̍s���p�^�[�����X�g9(����L���ړ��̓G)
/// FifthStage�̓G
/// </summary>
void EnemyBase::MapList9()
{
	positionList[8].push_back({ -2200.0f, 0.0f, 2200.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2200.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2800.0f });
	positionList[8].push_back({ -3300.0f, 0.0f, 2200.0f });

	itr[8] = positionList[8].begin();   //�C�e���[�^��擪�ɐݒ�
}