#include "SelectionUi.h"
#include "Stage.h"
#include "InputManager.h"

char stage1[16][16] =
{
	1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
	1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectionUi::SelectionUi()
	: fontHandle(0)
	, selectionKeyImage(0)
	, selectionUiImage(0)
	, stageDescription(0)
	, operationMethod(0)
	, SELECTION_FONT_SIZE(90)
	, FONT_THICK(1)
	, STAGE_NUMBER(2)
	, IMAGE_FOLDER_PATH("Data/Image/")
	, SELECTION_KEY_PATH("selection_key.png")
	, SELECTION_TITLE_PATH("selection_Ui.png")
	, STAGE_DESCRIPTION_PATH("stage_description.png")
	, OPERATION_METHOD_PATH("operation_method.png")
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SelectionUi::~SelectionUi()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void SelectionUi::Initialize()
{
	//�Z���N�V����Ui�摜�̓ǂݍ���
	stageDescription = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, STAGE_DESCRIPTION_PATH).c_str());

	selectionKeyImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, SELECTION_KEY_PATH).c_str());

	selectionUiImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, SELECTION_TITLE_PATH).c_str());

	operationMethod = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, OPERATION_METHOD_PATH).c_str());

	StagePop(stage1);

	//�t�H���g�f�[�^�̍쐬
	fontHandle = CreateFontToHandle("Oranienbaum", SELECTION_FONT_SIZE, 1);
}

/// <summary>
/// �I������
/// </summary>
void SelectionUi::Finalize()
{
	DeleteGraph(selectionKeyImage);

	DeleteGraph(stageDescription);

	DeleteGraph(operationMethod);

	DeleteGraph(selectionUiImage);

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(fontHandle);
}

/// <summary>
/// �X�e�[�W�o��
/// </summary>
/// <param name="stageData">�X�e�[�W�̃f�[�^</param>
void SelectionUi::StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_Z; i++)
	{
		for (int j = 0; j < BLOCK_NUM_X; j++)
		{
			float posX = i * 200.0f;
			float posZ = j * -200.0f;

			if (stageData[j][i] == 0)
			{
				activeStage.emplace_back(new Stage({ posX, 0.0f, posZ }, { 0.5f, 0.5f, 0.5f }));
			}
		}
	}
}

/// <summary>
/// �X�e�[�W��Ui�`�揈��
/// </summary>
/// <param name="mapNumber"></param>
/// <param name="enemyNumber"></param>
/// <param name="cakeNumber"></param>
void SelectionUi::StageUiDraw(int mapNumber, int enemyNumber, int cakeNumber)
{
	DrawGraph(100, 150, stageDescription, TRUE);

	//�G�ƃP�[�L�̐���\��
	DrawFormatStringToHandle(370, 470, GetColor(255, 255, 255), fontHandle, "%d", enemyNumber);
	DrawFormatStringToHandle(520, 570, GetColor(255, 255, 255), fontHandle, "%d", cakeNumber);

	for (auto itr = activeStage.begin(); itr != activeStage.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

/// <summary>
/// �^�C�g���֑J�ڂ���Ui�`�揈��
/// </summary>
void SelectionUi::TitleUiDraw()
{
	DrawRotaGraph(950, 550, 0.7, 0.0, selectionUiImage, TRUE);
}

/// <summary>
/// �`�揈��
/// </summary>
void SelectionUi::Draw()
{
	DrawRotaGraph(500, 950, 0.85, 0.0, operationMethod, TRUE);

	DrawRotaGraph(1450, 950, 0.6, 0.0, selectionKeyImage, TRUE);
}