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
		STONE,			//���΃��f��
		STAGE,			//�X�e�[�W���f��
		GOAL,			//�S�[���t���b�O���f��
		MODEL_AMOUNT,	//���f���̐�
	};

	static ModelManager& GetInstance();					  //�A�h���X��Ԃ�

	const int& GetModelHandle(ModelType modelType) const; //���f���n���h���̎Q�Ƃ�Ԃ�

private:
	ModelManager();
	ModelManager(const ModelManager&);		//�R�s�[�R���X�g���N�^
	virtual ~ModelManager();

	void LoadAllModel();		//�S�Ẵ��f���̓ǂݍ���
	void DeleteAllModel();		//�S�Ẵ��f���̍폜

	struct Model
	{
		string modelPath;		//���f���̃p�X
	};

	int modelHandle[MODEL_AMOUNT];	//���f���n���h��

	//�萔
	const string MODEL_FOLDER_PATH;	//Model�t�H���_�܂ł̃p�X
	const string PLAYER_PATH;		//player���f���t�@�C���̃p�X
	const string ENEMY_PATH;		//enemy���f���t�@�C���̃p�X
	const string ENEMY_VISUAL_PATH;	//enemy_visual���f���t�@�C���̃p�X
	const string CAKE_PATH;			//cake���f���t�@�C���̃p�X
	const string CAKE_HALF_PATH;	//cake_half���f���t�@�C���̃p�X
	const string STONE_PATH;		//stone���f���t�@�C���̃p�X
	const string STAGE_PATH;		//stage���f���t�@�C���̃p�X
	const string GOAL_FLAG_PATH;	//goal_flag���f���t�@�C���̃p�X
};