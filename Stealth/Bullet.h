#pragma once

#include "ObjectBase.h"
#include "Math3D.h"

class Boal;

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
	void Activate(VECTOR inPosition, VECTOR inDir);
	void Update(float deltaTime, Boal* boal);
	void Draw();


private:

	void OnShot(float deltaTime);			//���������ꂽ��

	//�ÓI�萔
	static const VECTOR SIZE;           //���f���̔{��
	static const float  SPEED;			//���f���̃X�s�[�h

};