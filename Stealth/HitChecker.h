#pragma once

class Player;
class Boal;


/// <summary>
/// �q�b�g�`�F�b�J�[�N���X
/// </summary>
class HitChecker final
{
public:
	 HitChecker();
	~HitChecker();

	void Check(Player* player, Boal* boal);			//�Փ˔���
	bool Hit() { return hit; }


private:

	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void BoalAndPlayer(Player* player, Boal* boal);			//�{�[���ƃv���C���[�̓����蔻��
	void MapAndPlayer();

	double direction;
	bool hit;				//�Փ˂����Ȃ��
	bool possessionBoal;	//�������Ă���{�[���̐�

};