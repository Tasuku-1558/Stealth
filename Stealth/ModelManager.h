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

	ModelManager();
	~ModelManager();

	//���f���̎��
	enum ModelType
	{
		PLAYER,			//�v���C���[���f��
		ENEMY,			//�G�l�~�[���f��
		ENEMY_VISUAL,	//�G�l�~�[�̎��샂�f��
		WALL,			//�ǃ��f��
		CAKE,			//�P�[�L���f��
		STAGE1,			//�X�e�[�W1���f��
		STAGE2,			//�X�e�[�W2���f��
		STAGE3,			//�X�e�[�W3���f��
		MODEL_AMOUNT	//���f���̌�
	};

	static ModelManager& GetInstance();					  //�A�h���X��Ԃ�

	const int& GetModelHandle(ModelType modelType) const; //���f���n���h���̎Q�Ƃ�Ԃ�

private:

	 ModelManager(const ModelManager&);			//�R�s�[�R���X�g���N�^

	 string InputPath(string folderPath,	//���f���̃p�X�����
					  string path);

	 void LoadAllModel();						//�S�Ẵ��f���̓ǂݍ���
	 void DeleteAllModel();						//�S�Ẵ��f���̍폜


	 int modelHandle[MODEL_AMOUNT];				//���f���n���h��

	 //�ÓI�萔
	 static const string MODEL_FOLDER_PATH;		//model�t�H���_�܂ł̃p�X
	 static const string PLAYER_PATH;			//player���f���t�@�C���̃p�X
	 static const string ENEMY_PATH;			//enemy���f���t�@�C���̃p�X
	 static const string ENEMY_VISUAL_PATH;		//enemy_visual���f���t�@�C���̃p�X
	 static const string WALL_PATH;				//wall���f���t�@�C���̃p�X
	 static const string CAKE_PATH;				//cake���f���t�@�C���̃p�X
	 static const string STAGE1_PATH;			//stage1���f���t�@�C���̃p�X
	 static const string STAGE2_PATH;			//stage2���f���t�@�C���̃p�X
	 static const string STAGE3_PATH;			//stage3���f���t�@�C���̃p�X

};