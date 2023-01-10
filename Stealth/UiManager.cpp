#include "UiManager.h"
#include "Enemy.h"
#include "HitChecker.h"

using std::string;

const string UiManager::FOLDER_PATH		   = "data/image/";		//�摜�t�@�C���̃p�X
const string UiManager::UI_GRAPHIC_PATH    = "ui";				//UI�摜
const string UiManager::FILENAME_EXTENSION = ".png";			//�摜�g���q


UiManager::UiManager()
	: uiHandle()
	, count(0)
{
	//�����Ȃ�
}

UiManager::~UiManager()
{
	//�I���������Ă΂�ĂȂ����
	if (uiHandle[0] != NULL)
	{
		Finalize();
	}
}

void UiManager::Initialize()
{
	//UI�摜�ǂݍ���
	string failePath = FOLDER_PATH + UI_GRAPHIC_PATH; // �t�H���_�p�X + �t�@�C����
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

void UiManager::Finalize()
{
	for (int i = 0; i < GRAPHIC_AMOUNT; ++i)
	{
		DeleteGraph(uiHandle[i]);
		uiHandle[i] = NULL;
	}
}

void UiManager::Draw(PlayScene::State state, Enemy* enemy, HitChecker* hitChecker)
{
	//�����o���摜�`��
	DrawBillboard3D(VGet(-800.0f, 0.0f, 0.0f), 0.5f, 0.5f, 200.0f, 0.0f, uiHandle[BALLOON], TRUE);

	switch (state)
	{
	case PlayScene::START:
		
		break;

	case PlayScene::GAME:
		StartGameDraw();
		PlayerHpDraw(enemy);
		OperationMethodDraw(hitChecker);
		break;
	}
}

/// <summary>
/// �Q�[���J�nUI
/// </summary>
void UiManager::StartGameDraw()
{
	count++;

	if (count < 50)
	{
		DrawGraph(0, -50, uiHandle[STARGE1], TRUE);
	}
}

/// <summary>
/// ������@����UI
/// </summary>
/// <param name="hitChecker"></param>
void UiManager::OperationMethodDraw(HitChecker* hitChecker)
{
	if (hitChecker->UI())
	{
		DrawGraph(0, 20, uiHandle[OPERATION], TRUE);
	}
}

/// <summary>
/// �v���C���[HPUI
/// </summary>
/// <param name="enemy"></param>
void UiManager::PlayerHpDraw(Enemy* enemy)
{
	DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);
	DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP_FRAME], TRUE);

	if (enemy->GetPlayerCount() == 0)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(310, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (enemy->GetPlayerCount() == 1)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
		DrawRotaGraph(205, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
	else if (enemy->GetPlayerCount() == 2)
	{
		DrawRotaGraph(100, 70, 0.5f, 0, uiHandle[PLAYER_HP], TRUE);
	}
}