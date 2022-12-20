#pragma once

#include "ObjectBase.h"
#include "Math3D.h"

class Player;

/// <summary>
/// �v���C���[�V���b�g�N���X
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet();
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate(/*Player* player*/);
	void Update();
	void Draw();


private:

	void OnShot();			//���������ꂽ��

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const float  SPEED;			//���f���̃X�s�[�h

};