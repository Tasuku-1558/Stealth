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

	void Check(Player* player, Boal* boal);
	bool Hit() { return hit; }

	//�f�o�b�N�p
	bool PossessionBoal() { return possessionBoal; }

private:

	HitChecker(const HitChecker&);		//�R�s�[�R���X�g���N�^

	void BoalAndPlayer(Player* player, Boal* boal);

	double direction;
	bool hit;				//�Փ˂����Ȃ��
	bool possessionBoal;	//�������Ă���{�[���̐�

};