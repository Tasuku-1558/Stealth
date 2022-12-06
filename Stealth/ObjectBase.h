#pragma once

#include "DxLib.h"


class ObjectBase
{
public:
			  ObjectBase();		//�R���X�g���N�^
	  virtual~ObjectBase();		//�f�X�g���N�^

	  virtual void Initialize() = 0;
	  virtual void Activate() = 0;
	  //virtual void Update(float dltaTime) = 0;				
	  virtual void Draw() = 0;

	  const VECTOR& GetPosition() const; 	//position��getter
	  const VECTOR& GetDir() const;			//dir��getter

protected:
	VECTOR position;						//���݂̍��W
	VECTOR dir;								//�����x�N�g��
	int	   modelHandle;						//���f���n���h��

};