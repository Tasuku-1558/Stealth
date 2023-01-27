#include "SelectionUi.h"


const string SelectionUi::IMAGE_FOLDER_PATH		  = "data/image/";				//image�t�H���_�܂ł̃p�X
const string SelectionUi::SELECTION_KEY_PATH	  = "selection_key.png";		//�X�e�[�W�Z���N�V����UI�摜�̃p�X
const string SelectionUi::STAGE1_DESCRIPTION_PATH = "stage1_description.png";	//�X�e�[�W1�̐����摜�̃p�X
const string SelectionUi::STAGE2_DESCRIPTION_PATH = "stage2_description.png";	//�X�e�[�W2�̐����摜�̃p�X
const int	 SelectionUi::STAGE_NUMBER			  = 2;							//�X�e�[�W��

const VECTOR SelectionUi::STAGE1_POSITION		  = { 1300.0f, 740.0f, 0.0f };	//�X�e�[�W1���f���̈ʒu
const VECTOR SelectionUi::STAGE1_SIZE			  = { 10.0f, 10.0f, 10.0f };	//�X�e�[�W1���f���̔{��
const VECTOR SelectionUi::STAGE1_ROTATE = { 80.0f * DX_PI_F / 180.0f, 190.0f * DX_PI_F / 180.0f, 0.0f }; //�X�e�[�W1���f���̉�]�l

const VECTOR SelectionUi::STAGE2_POSITION		  = { 1400.0f, 300.0f, -100.0f };	//�X�e�[�W2���f���̈ʒu
const VECTOR SelectionUi::STAGE2_SIZE			  = { 8.0f, 8.0f, 8.0f };			//�X�e�[�W2���f���̔{��
const VECTOR SelectionUi::STAGE2_ROTATE = { 80.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f }; //�X�e�[�W2���f���̉�]�l


/// <summary>
/// �R���X�g���N�^
/// </summary>
SelectionUi::SelectionUi()
	: selectionKeyImage(0)
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
	string failePath = IMAGE_FOLDER_PATH + STAGE1_DESCRIPTION_PATH;
	stageDescription[0] = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + STAGE2_DESCRIPTION_PATH;
	stageDescription[1] = LoadGraph(failePath.c_str());

	failePath = IMAGE_FOLDER_PATH + SELECTION_KEY_PATH;
	selectionKeyImage = LoadGraph(failePath.c_str());

	//�X�e�[�W1�̃}�b�v���f��
	MapInput(0, ModelManager::STAGE1, STAGE1_POSITION, STAGE1_SIZE, STAGE1_ROTATE);

	//�X�e�[�W2�̃}�b�v���f��
	MapInput(1, ModelManager::STAGE2, STAGE2_POSITION, STAGE2_SIZE, STAGE2_ROTATE);
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
/// �`�揈��
/// </summary>
void SelectionUi::Draw()
{
	DrawRotaGraph(1350, 950, 0.7f, 0, selectionKeyImage, TRUE);
}

/// <summary>
/// �X�e�[�W1��UI�`�揈��
/// </summary>
void SelectionUi::Stage1_Draw()
{
	DrawGraph(100, 150, stageDescription[0], TRUE);
	MV1DrawModel(modelHandle[0]);
}

/// <summary>
/// �X�e�[�W2��UI�`�揈��
/// </summary>
void SelectionUi::Stage2_Draw()
{
	DrawGraph(100, 150, stageDescription[1], TRUE);
	MV1DrawModel(modelHandle[1]);
}