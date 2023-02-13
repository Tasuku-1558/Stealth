#pragma once

#include <vector>
#include <string>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;


/// <summary>
/// �Ď��G�l�~�[�N���X
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(const VECTOR& pos, VECTOR changeDir);
	virtual ~MonitoringEnemy();

	void Initialize();									//����������
	void Activate();									//����������
	void Update(float deltaTime, Player* player);		//�X�V����
	void Draw();										//�`�揈��

	const bool Spotted() { return playerSpotted; }			//�v���C���[�����������ǂ�����Ԃ�

private:
	MonitoringEnemy(const MonitoringEnemy&);	//�R�s�[�R���X�g���N�^

	void VisualAnglePlayer(Player* player);		//�G�l�~�[�̎���Ƀv���C���[���������ꍇ
	void DirMove(float deltaTime);				//�G�l�~�[�̌����̏���
	void Reaction();							//�G�l�~�[�̃v���C���[�̔���
	void ReactionDraw();						//���A�N�V�����摜�̕`�揈��
	void Finalize();							//�I������

	std::string InputPath(std::string folderPath, //�摜�̃p�X�����
						  std::string imagePath);

	float dirCount;			//�����ύX�J�E���g
	VECTOR anotherDir;		//�ʂ̌���

	//�ÓI�萔
	static const std::string IMAGE_FOLDER_PATH;	//image�t�H���_�܂ł̃p�X
	static const std::string PLAYER_FIND_PATH;	//�v���C���[���������摜�̃p�X
	static const std::string MARK_PATH;			//�r�b�N���}�[�N�摜�̃p�X
};