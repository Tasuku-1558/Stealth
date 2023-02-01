#pragma once

#include "DxLib.h"


/// <summary>
/// ObjectBase�N���X
/// </summary>
class ObjectBase
{
public:
	  ObjectBase();
	  virtual~ObjectBase();

	  virtual void Initialize() = 0;					//����������
	  //virtual void Update(float dltaTime) = 0;		//�X�V����
	  //virtual void Draw() = 0;						//�`�揈��

	  const VECTOR& GetPosition() const; 	//position��getter
	  const VECTOR& GetDir() const;			//dir��getter
	  const int& GetModelHandle() const; 	//modelHandle��getter

	  //�I�u�W�F�N�g�̃^�O
	  enum class Object
	  {
		  PLAYER,		//�v���C���[
		  CAKE,			//�P�[�L
		  WALL,			//��
	  };

protected:
	VECTOR position;	//���݂̍��W
	VECTOR dir;			//�����x�N�g��
	int modelHandle;	//���f���n���h��
	Object object;		//�I�u�W�F�N�g�̃^�O
};