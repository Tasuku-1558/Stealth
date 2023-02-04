#pragma once

#include "SceneBase.h"
#include <vector>

class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class MonitoringEnemy;
class BallBullet;
class HitChecker;
class ThirdStageMap;
class CakeRepopEffect;
class UiManager;


/// <summary>
/// ThirdStage�N���X
/// </summary>
class ThirdStage final : public SceneBase
{
public:
	ThirdStage(SceneManager* const sceneManager);
	virtual ~ThirdStage();

	void Initialize();				//����������
	void Finalize();				//�I������
	void Activate();				//����������
	void Update(float deltaTime);	//�X�V����
	void Draw();					//�`�揈��

	//�Q�[���̏��
	enum class State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
		GOAL,	//�S�[��
	};

private:
	ThirdStage(const ThirdStage&);	//�R�s�[�R���X�g���N�^


	void EntryBallBullet(BallBullet* newBallBullet);		//�{�[���o���b�g��o�^
	void DeleteBallBullet(BallBullet* deleteBallBullet);	//�{�[���o���b�g���폜
	void BallBulletPop();									//�{�[���o���b�g�̏o��
	
	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	std::vector<Enemy*> enemy;
	MonitoringEnemy* monitoringEnemy;
	std::vector<BallBullet*> ballBullet;
	HitChecker* hitChecker;
	ThirdStageMap* thirdStageMap;
	CakeRepopEffect* cakeEffect;
	UiManager* uiManager;


	void UpdateStart(float deltaTime);						//�Q�[���J�n�O
	void UpdateGame(float deltaTime);						//�Q�[����
	void UpdateGoal(float deltaTime);						//�S�[��
	void (ThirdStage::* pUpdate)(float deltaTime);			//Update�֐��|�C���^


	State state;		//�Q�[���̏��
	int  font;			//�Q�[���t�H���g

	//�ÓI�萔
	//static const int GOAL_POSITION_X;					//�S�[���̈ʒu


};