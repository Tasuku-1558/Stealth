#pragma once

#include "ObjectBase.h"
#include "Math3D.h"


/// <summary>
/// �v���C���[�V���b�g�N���X
/// </summary>
class Shot final : public ObjectBase
{
public:
	 Shot();
	~Shot();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(VECTOR position);
	void Draw();


private:

	void OnShot(VECTOR position);			//���������ꂽ��

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	//static const VECTOR POSITION;		//���f���̈ʒu
	static const float  SPEED;			//���f���̃X�s�[�h
	static const VECTOR DIR;

};