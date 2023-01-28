#pragma once

#include "SceneBase.h"
#include "PreCompiledHeader.h"
#include <vector>

class Player;
class Enemy;
class Camera;
class Light;
class BackGround;
class BallBullet;
class Wall;
class HitChecker;
class SecondStageMap;
class Cake_Repop_Effect;
class UiManager;
class FadeManager;


/// <summary>
/// SecondStage�N���X
/// </summary>
class SecondStage final : public SceneBase
{
public:
	 SecondStage(SceneManager* const sceneManager);
	 virtual ~SecondStage();

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
	SecondStage(const SecondStage&);		//�R�s�[�R���X�g���N�^

	Player* player;
	std::vector<Enemy*> enemy;
	Camera* camera;
	Light* light;
	BackGround* backGround;
	std::vector<BallBullet*> ballBullet;
	std::vector<Wall*> wall;
	HitChecker* hitChecker;
	SecondStageMap* secondStageMap;
	Cake_Repop_Effect* cakeEffect;
	UiManager* uiManager;
	FadeManager* fadeManager;
	

	void EntryEnemy(Enemy* newEnemy);						//�G�l�~�[��o�^
	void DeleteEnemy(Enemy* deleteEnemy);					//�G�l�~�[���폜
	void EnemyPop();										//�G�l�~�[�̏o��

	void EntryBallBullet(BallBullet* newBallBullet);		//�{�[���o���b�g��o�^
	void DeleteBallBullet(BallBullet* deleteBallBullet);	//�{�[���o���b�g���폜
	void BallBulletPop();									//�{�[���o���b�g�̏o��

	void EntryWall(Wall* newWall);							//�ǂ�o�^
	void DeleteWall(Wall* deleteWall);						//�ǂ��폜
	void WallPop();											//�ǂ̏o��

	void UpdateStart(float deltaTime);						//�Q�[���J�n�O
	void UpdateGame(float deltaTime);						//�Q�[����
	void UpdateGoal(float deltaTime);						//�S�[��
	void (SecondStage::* pUpdate)(float deltaTime);			//Update�֐��|�C���^

	State state;		//�Q�[���̏��
	int font;			//�Q�[���t�H���g
	bool enemyPop;		//�G�l�~�[�̏o���t���O
	bool ballPop;		//�{�[���̏o���t���O
	bool wallPop;		//�ǂ̏o���t���O
	int count;
};