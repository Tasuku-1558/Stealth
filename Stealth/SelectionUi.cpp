#include "SelectionUi.h"


const string SelectionUi::IMAGE_FOLDER_PATH		  = "data/image/";				//image�t�H���_�܂ł̃p�X
const string SelectionUi::SELECTION_KEY_PATH	  = "selection_key.png";		//�X�e�[�W�Z���N�V����UI�摜�̃p�X
const string SelectionUi::SELECTION_TITLE_PATH	  = "selection_Ui.png";			//�X�e�[�W�Z���N�V��������^�C�g���֑J�ڂ�UI�摜
const string SelectionUi::STAGE1_DESCRIPTION_PATH = "stage1_description.png";	//�X�e�[�W1�̐����摜�̃p�X
const string SelectionUi::STAGE2_DESCRIPTION_PATH = "stage2_description.png";	//�X�e�[�W2�̐����摜�̃p�X
const string SelectionUi::STAGE3_DESCRIPTION_PATH = "stage3_description.png";	//�X�e�[�W3�̐����摜�̃p�X
const string SelectionUi::STAGE4_DESCRIPTION_PATH = "stage4_description.png";	//�X�e�[�W4�̐����摜�̃p�X
const int	 SelectionUi::STAGE_NUMBER			  = 4;							//�X�e�[�W��

const VECTOR SelectionUi::STAGE1_POSITION		  = { 1300.0f, 740.0f, 0.0f };		//�X�e�[�W1���f���̈ʒu
const VECTOR SelectionUi::STAGE1_SIZE			  = { 10.0f, 10.0f, 10.0f };		//�X�e�[�W1���f���̔{��
const VECTOR SelectionUi::STAGE1_ROTATE = { 80.0f * DX_PI_F / 180.0f, 190.0f * DX_PI_F / 180.0f, 0.0f }; //�X�e�[�W1���f���̉�]�l

const VECTOR SelectionUi::STAGE2_POSITION		  = { 900.0f, 1050.0f, 0.0f };		//�X�e�[�W2���f���̈ʒu
const VECTOR SelectionUi::STAGE2_SIZE			  = { 9.0f, 9.0f, 9.0f };			//�X�e�[�W2���f���̔{��
const VECTOR SelectionUi::STAGE2_ROTATE = { 80.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f }; //�X�e�[�W2���f���̉�]�l

const VECTOR SelectionUi::STAGE3_POSITION		  = { 1250.0f, 750.0f, -150.0f };	//�X�e�[�W3���f���̈ʒu
const VECTOR SelectionUi::STAGE3_SIZE			  = { 7.0f, 7.0f, 7.0f };			//�X�e�[�W3���f���̔{��
const VECTOR SelectionUi::STAGE3_ROTATE = { 90.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 0.0f }; //�X�e�[�W3���f���̉�]�l

const VECTOR SelectionUi::STAGE4_POSITION		  = { 1100.0f, 800.0f, -150.0f };	//�X�e�[�W4���f���̈ʒu
const VECTOR SelectionUi::STAGE4_SIZE			  = { 6.0f, 6.0f, 6.0f };			//�X�e�[�W4���f���̔{��
const VECTOR SelectionUi::STAGE4_ROTATE = { 90.0f * DX_PI_F / 180.0f, 190.0f * DX_PI_F / 180.0f, 0.0f }; //�X�e�[�W4���f���̉�]�l


/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectionUi::SelectionUi()
	: selectionKeyImage(0)
	, selectionUiImage(0)
	, stageDescription()
	, modelHandle()
	, position()
{
	//�����Ȃ�
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
	//�摜�ǂݍ���
	stageDescription[0] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, STAGE1_DESCRIPTION_PATH).c_str());

	stageDescription[1] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, STAGE2_DESCRIPTION_PATH).c_str());

	stageDescription[2] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, STAGE3_DESCRIPTION_PATH).c_str());

	stageDescription[3] = LoadGraph(InputPath(IMAGE_FOLDER_PATH, STAGE4_DESCRIPTION_PATH).c_str());

	selectionKeyImage   = LoadGraph(InputPath(IMAGE_FOLDER_PATH, SELECTION_KEY_PATH).c_str());

	selectionUiImage	= LoadGraph(InputPath(IMAGE_FOLDER_PATH, SELECTION_TITLE_PATH).c_str());


	//�}�b�v���f���ǂݍ���
	MapInput(0, ModelManager::STAGE1, STAGE1_POSITION, STAGE1_SIZE, STAGE1_ROTATE);

	MapInput(1, ModelManager::STAGE2, STAGE2_POSITION, STAGE2_SIZE, STAGE2_ROTATE);

	MapInput(2, ModelManager::STAGE3, STAGE3_POSITION, STAGE3_SIZE, STAGE3_ROTATE);

	MapInput(3, ModelManager::STAGE4, STAGE4_POSITION, STAGE4_SIZE, STAGE4_ROTATE);

}

/// <summary>
/// �}�b�v������
/// </summary>
/// <param name="number"></param>
/// <param name="modelType"></param>
/// <param name="mapPos"></param>
/// <param name="size"></param>
/// <param name="rotate"></param>
void SelectionUi::MapInput(int number, ModelManager::ModelType modelType, VECTOR mapPos, VECTOR size, VECTOR rotate)
{
	modelHandle[number] = MV1DuplicateModel(ModelManager::GetInstance().GetModelHandle(modelType));
	position[number] = mapPos;
	MV1SetScale(modelHandle[number], size);
	MV1SetRotationXYZ(modelHandle[number], rotate);
	MV1SetPosition(modelHandle[number], position[number]);
}

/// <summary>
/// �摜�̃p�X�����
/// </summary>
/// <param name="folderPath"></param>
/// <param name="path"></param>
/// <returns></returns>
std::string SelectionUi::InputPath(std::string folderPath, std::string path)
{
	return std::string(folderPath + path);
}

/// <summary>
/// ����������
/// </summary>
void SelectionUi::Activate()
{
}

/// <summary>
/// �I������
/// </summary>
void SelectionUi::Finalize()
{
	for (int i = 0; i < STAGE_NUMBER; i++)
	{
		DeleteGraph(stageDescription[i]);

		MV1DeleteModel(modelHandle[i]);
	}

	DeleteGraph(selectionKeyImage);
}

/// <summary>
/// �X�e�[�W��UI�`�揈��
/// </summary>
/// <param name="number"></param>
void SelectionUi::StageUiDraw(int number)
{
	DrawGraph(100, 150, stageDescription[number], TRUE);
	MV1DrawModel(modelHandle[number]);
}

/// <summary>
/// �^�C�g���֑J�ڂ���UI�`�揈��
/// </summary>
void SelectionUi::TitleUiDraw()
{
	DrawRotaGraph(950, 550, 0.7f, 0, selectionUiImage, TRUE);
}

/// <summary>
/// �`�揈��
/// </summary>
void SelectionUi::Draw()
{
	DrawRotaGraph(1350, 950, 0.7f, 0, selectionKeyImage, TRUE);
}