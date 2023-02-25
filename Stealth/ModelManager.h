#pragma once

#include <string>

using namespace std;

/// <summary>
/// �V���O���g��
/// ���f���Ǘ��N���X
/// </summary>
class ModelManager final
{
public:

	//���f���̎��
	enum ModelType
	{
		PLAYER,			//�v���C���[���f��
		ENEMY,			//�G�l�~�[���f��
		ENEMY_VISUAL,	//�G�l�~�[�̎��샂�f��
		CAKE,			//�P�[�L���f��
		CAKE_HALF,		//�P�[�L�������̃��f��
		STAGE1,			//�X�e�[�W1���f��
		STAGE2,			//�X�e�[�W2���f��
		STAGE3,			//�X�e�[�W3���f��
		STAGE4,			//�X�e�[�W4���f��
		STAGE5,			//�X�e�[�W5���f��
		GOAL,			//�S�[���t���b�O���f��
		MODEL_AMOUNT	//���f���̌�
	};

	static ModelManager& GetInstance();					  //�A�h���X��Ԃ�

	const int& GetModelHandle(ModelType modelType) const; //���f���n���h���̎Q�Ƃ�Ԃ�

private:
	ModelManager();
	ModelManager(const ModelManager&);			//�R�s�[�R���X�g���N�^
	virtual ~ModelManager();

	string InputPath(string folderPath,			//���f���̃p�X�����
					 string modelPath);

	void LoadAllModel();						//�S�Ẵ��f���̓ǂݍ���
	void DeleteAllModel();						//�S�Ẵ��f���̍폜

	int modelHandle[MODEL_AMOUNT];				//���f���n���h��

	//�萔
	const string MODEL_FOLDER_PATH;	//model�t�H���_�܂ł̃p�X
	const string PLAYER_PATH;		//player���f���t�@�C���̃p�X
	const string ENEMY_PATH;		//enemy���f���t�@�C���̃p�X
	const string ENEMY_VISUAL_PATH;	//enemy_visual���f���t�@�C���̃p�X
	const string CAKE_PATH;			//cake���f���t�@�C���̃p�X
	const string CAKE_HALF_PATH;	//cake_half���f���t�@�C���̃p�X
	const string STAGE1_PATH;		//stage1���f���t�@�C���̃p�X
	const string STAGE2_PATH;		//stage2���f���t�@�C���̃p�X
	const string STAGE3_PATH;		//stage3���f���t�@�C���̃p�X
	const string STAGE4_PATH;		//stage4���f���t�@�C���̃p�X
	const string STAGE5_PATH;		//stage5���f���t�@�C���̃p�X
	const string GOAL_FLAG_PATH;	//goal_flag���f���t�@�C���̃p�X

};