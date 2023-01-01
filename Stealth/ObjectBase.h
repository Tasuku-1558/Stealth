#pragma once

#include "DxLib.h"


/// <summary>
/// �I�u�W�F�N�g�x�[�X�N���X
/// </summary>
class ObjectBase
{
public:
			  ObjectBase();		//�R���X�g���N�^
	  virtual~ObjectBase();		//�f�X�g���N�^

	  virtual void Initialize() = 0;
	  //virtual void Activate() = 0;
	  //virtual void Update(float dltaTime) = 0;				
	  virtual void Draw() = 0;

	  const VECTOR& GetPosition() const; 	//position��getter
	  const VECTOR& GetDir() const;			//dir��getter


	  //�I�u�W�F�N�g�̃^�O
	  enum Object
	  {
		  PLAYER,
		  BOAL,
		  WALL,
	  };


protected:
	VECTOR position;						//���݂̍��W
	VECTOR dir;								//�����x�N�g��
	int modelHandle;						//���f���n���h��

};