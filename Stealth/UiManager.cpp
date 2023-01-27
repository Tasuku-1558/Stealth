#include "UiManager.h"

using std::string;

const string UiManager::IMAGE_FOLDER_PATH  = "data/image/";		//�摜�t�@�C���̃p�X
const string UiManager::UI_GRAPHIC_PATH    = "ui";				//UI�摜
const string UiManager::FILENAME_EXTENSION = ".png";			//�摜�g���q


/// <summary>
/// �R���X�g���N�^
/// </summary>
UiManager::UiManager()
	: uiHandle()
	, stageCount(0)
{
	//�����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UiManager::~UiManager()
{
	//�I���������Ă΂�ĂȂ����
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

/// <summary>
/// ����������
/// </summary>
void UiManager::Initialize()
{
	//UI�摜�ǂݍ���
	string failePath = IMAGE_FOLDER_PATH + UI_GRAPHIC_PATH;		// �t�H���_�p�X + �t�@�C����
	string fullPath = failePath;
	
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		fullPath = failePath + std::to_string(i) + FILENAME_EXTENSION;
		uiHandle[i] = LoadGraph(fullPath.c_str());

		if (uiHandle[i] < 0)
		{
			printfDx("�摜�ǂݍ��݂Ɏ��s[%d]\n", i);
		}
	}
}

/// <summary>
/// ����������
/// </summary>
void UiManager::Activate()
{
	stageCount = 0;
}

/// <summary>
/// �I������
/// </summary>
void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}
}

/// <summary>
/// FirstStage��UI�`�揈��
/// </summary>
/// <param name="state"></param>
/// <param name="playerCount"></param>
/// <param name="hitUi"></param>
void UiManager::Draw(FirstStage::State state, int playerCount, bool hitUi)
{
	//�����o���摜�`��
	DrawBillboard3D(VGet(-800.0f, 0.0f, 0.0f), 0.5f, 0.5f, 200.0f, 0.0f, uiHandle[BALLOON], TRUE);

	switch (state)
	{
	case FirstStage::State::START:
		
		break;

	case FirstStage::State::GAME:

		StartGameDraw(STAGE1);
		PlayerHpDraw(playerCount);
		OperationMethodDraw(hitUi);
		DrawGraph(0, 900, uiHandle[KEY], TRUE);		//WASD�L�[�`��
		break;

	case FirstStage::State::GOAL:
		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
		break;
	}
}

/// <summary>
/// SecondStage��UI�`�揈��
/// </summary>
/// <param name="state"></param>
/// <param name="playerCount"></param>
void UiManager::Draw(SecondStage::State state, int playerCount)
{
	switch (state)
	{
	case SecondStage::State::START:
		
		break;

	case SecondStage::State::GAME:
		
		StartGameDraw(STAGE2);
		PlayerHpDraw(playerCount);
		DrawGraph(0, 900, uiHandle[KEY], TRUE);		//WASD�L�[�`��
		break;

	case SecondStage::State::GOAL:
		DrawRotaGraph(950, 900, 0.5f, 0, uiHandle[CLEAR], TRUE);
		break;
	}
}

/// <summary>
/// �Q�[���J�nUI
/// </summary>
/// <param name="graphic"></param>
void UiManager::StartGameDraw(UiManager::Graphic graphic)
{
	stageCount++;

	if (stageCount < 50)
	{
		DrawGraph(0, -50, uiHandle[graphic], TRUE);
	}
}

/// <summary>
/// ������@����UI
/// </summary>
/// <param name="hitUi"></param>
void UiManager::OperationMethodDraw(bool hitUi)
{
	if (hitUi)
	{
		DrawGraph(0, 20, uiHandle[OPERATION], TRUE);
	}
}

/// <summary>
/// �{�[���������Ă��邩��UI
/// </summary>
/// <param name="ballGet"></param>
void UiManager::BallGetDraw(bool ballGet)
{
	DrawGraph(0, 500, uiHandle[BALL_FRAME], TRUE);

	//�{�[���������Ă���Ȃ�
	if (ballGet)
	{
		DrawGraph(0, 500, uiHandle[BALL], TRUE);
	}
}

/// <summary>
/// �v���C���[HPUI
/// </summary>
/// <param name="playerCount"></param>
void UiManager::PlayerHpDraw(int playerCount)
{
	DrawRotaGraph(515, 150, 0.7f, 0, uiHandle[FRAME], TRUE);

	DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);
	DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);

	if (playerCount == 0)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (playerCount == 1)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (playerCount == 2)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
}