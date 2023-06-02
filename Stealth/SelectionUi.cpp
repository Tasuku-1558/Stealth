#include "SelectionUi.h"
#include "InputManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectionUi::SelectionUi()
	: fontHandle(0)
	, selectionUiImage()
	, stagePos()
	, SELECTION_UI_NUMBER(4)
	, SELECTION_FONT_SIZE(90)
	, FONT_THICK(1)
	, STAGE_NUMBER(2)
	, STAGE_POS_Y(150.0f)
	, BLOCK_SIZE({ 0.3f, 0.3f, 0.3f })
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
	Ui ui[] =
	{
		{SELECTION_KEY_PATH},
		{SELECTION_TITLE_PATH},
		{STAGE_DESCRIPTION_PATH},
		{OPERATION_METHOD_PATH},
	};

	//�Z���N�V����Ui�摜�̓ǂݍ���
	for (int i = 0; i < SELECTION_UI_NUMBER; i++)
	{
		selectionUiImage[i] = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, ui[i].imagePath).c_str());
	}

	StageList stageList[] =
	{
		{1, "Data/Csv/Stage1.csv"},
		{2, "Data/Csv/Stage2.csv"},
		{3, "Data/Csv/Stage1.csv"},
		{4, "Data/Csv/Stage1.csv"},
		{5, "Data/Csv/Stage1.csv"},
	};

	//CSV�t�@�C���̓ǂݍ���
	for (int i = 0; i < MAX_STAGE_NUMBER; i++)
	{
		stageData = new StageData(stageList[i].csvName);
	}

	StagePop();

	//�t�H���g�f�[�^�̍쐬
	fontHandle = CreateFontToHandle("Oranienbaum", SELECTION_FONT_SIZE, FONT_THICK);
}

/// <summary>
/// �I������
/// </summary>
void SelectionUi::Finalize()
{
	for (int i = 0; i < SELECTION_UI_NUMBER; i++)
	{
		DeleteGraph(selectionUiImage[i]);
	}

	//�쐬�����t�H���g�f�[�^�̍폜
	DeleteFontToHandle(fontHandle);
}

/// <summary>
/// �X�e�[�W�̏o��
/// </summary>
void SelectionUi::StagePop()
{
	stagePos.y = STAGE_POS_Y;

	for (int i = 0; i < BLOCK_NUM; i++)
	{
		for (int j = 0; j < BLOCK_NUM; j++)
		{
			stagePos.x = i * 100.0f;
			stagePos.z = (j * -100.0f) + 900.0f;

			if (stageData->stageNum[j * BLOCK_NUM + i] == 0)
			{
				activeStage.emplace_back(new StageBlock(stagePos, BLOCK_SIZE));
			}
		}
	}
}

/// <summary>
/// �X�e�[�W��Ui�`�揈��
/// </summary>
/// <param name="stageNumber">�X�e�[�W�̔ԍ�</param>
/// <param name="enemyNumber">�G�̐�</param>
/// <param name="cakeNumber">�P�[�L�̐�</param>
void SelectionUi::StageUiDraw(int stageNumber, int enemyNumber, int cakeNumber)
{
	DrawGraph(100, 150, selectionUiImage[Image::DESCRIPTION], TRUE);

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
	DrawRotaGraph(950, 550, 0.7, 0.0, selectionUiImage[Image::TITLE], TRUE);
}

/// <summary>
/// �`�揈��
/// </summary>
void SelectionUi::Draw()
{
	DrawRotaGraph(500, 950, 0.85, 0.0, selectionUiImage[Image::OPERATION_METHOD], TRUE);

	DrawRotaGraph(1450, 950, 0.6, 0.0, selectionUiImage[Image::KEY], TRUE);
}