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
		WALL,			//�ǃ��f��
		BALL,			//�{�[�����f��
		STAGE1,			//�X�e�[�W1���f��
		STAGE2,			//�X�e�[�W2���f��
		MODEL_AMOUNT	//���f���̌�
	};

	static ModelManager& GetInstance();					  // �A�h���X��Ԃ�

	const int& GetModelHandle(ModelType modelType) const; // ���f���n���h���̎Q�Ƃ�Ԃ�

private:

	 ModelManager();							//�R���X�g���N�^
	~ModelManager();							//�f�X�g���N�^

	 ModelManager(const ModelManager&);			//�R�s�[�R���X�g���N�^

	 void LoadAllModel();						//�S�Ẵ��f���̓ǂݍ���
	 void DeleteAllModel();						//�S�Ẵ��f���̍폜


	 int modelHandle[MODEL_AMOUNT];				//���f���n���h��

	 //�ÓI�萔
	 static const string MODEL_FOLDER_PATH;		//model�t�H���_�܂ł̃p�X
	 static const string PLAYER_PATH;			//player���f���t�@�C���̃p�X
	 static const string ENEMY_PATH;			//enemy���f���t�@�C���̃p�X
	 static const string WALL_PATH;				//wall���f���t�@�C���̃p�X
	 static const string BALL_PATH;				//ball���f���t�@�C���̃p�X
	 static const string STAGE1_PATH;			//stage1���f���t�@�C���̃p�X
	 static const string STAGE2_PATH;			//stage2���f���t�@�C���̃p�X
};