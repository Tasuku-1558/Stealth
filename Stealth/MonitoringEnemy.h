#pragma once

#include <vector>
#include <string>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;
class HitChecker;

using namespace std;

/// <summary>
/// �Ď��G�l�~�[�N���X
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(const VECTOR& pos, VECTOR changeDir, VECTOR currentDir);
	virtual ~MonitoringEnemy();

	void Initialize();									//����������
	void Activate();									//����������
	void Update(float deltaTime, Player* player, HitChecker* hitChecker);	//�X�V����
	void Draw();										//�`�揈��

	const bool Spotted() { return playerSpotted; }			//�v���C���[�����������ǂ�����Ԃ�

private:
	MonitoringEnemy(const MonitoringEnemy&);	//�R�s�[�R���X�g���N�^

	void VisualAnglePlayer(Player* player);		//�G�l�~�[�̎���Ƀv���C���[���������ꍇ
	void DirMove(float deltaTime);				//�G�l�~�[�̌����̏���
	void Reaction();							//�G�l�~�[�̃v���C���[�̔���
	void ReactionDraw();						//���A�N�V�����摜�̕`�揈��
	void Finalize();							//�I������

	string InputPath(string folderPath,			//�摜�̃p�X�����
					 string imagePath);

	float dirCount;			//�����ύX�J�E���g
	VECTOR anotherDir;		//�ʂ̌���
	VECTOR initialDir;		//�����̌���

	//�萔
	const string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	const string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
};