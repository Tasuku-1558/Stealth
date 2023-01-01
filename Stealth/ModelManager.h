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
		PLAYER_BODY,
		PLAYER_ARM,
		ENEMY_BODY,
		BOAL,
		STAGE1,
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
	 static const string PLAYER_BODY_PATH;		//player_body���f���t�@�C���̃p�X
	 static const string PLAYER_ARM_PATH;		//player_arm���f���t�@�C���̃p�X
	 static const string ENEMY_BODY_PATH;		//enemy_body���f���t�@�C���̃p�X
	 static const string BOAL_PATH;				//boal���f���t�@�C���̃p�X
	 static const string STAGE1_PATH;			//stage1���f���t�@�C���̃p�X

};