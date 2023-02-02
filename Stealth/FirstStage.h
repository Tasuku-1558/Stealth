#pragma once

#include "SceneBase.h"

class Camera;
class Light;
class BackGround;
class Player;
class Enemy;
class BallBullet;
class Wall;
class HitChecker;
class FirstStageMap;
class CakeRepopEffect;
class UiManager;
class FadeManager;

/// <summary>
/// FirstStage�N���X
/// </summary>
class FirstStage final : public SceneBase
{
public:
	 FirstStage(SceneManager* const sceneManager);
	 virtual ~FirstStage();

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
	FirstStage(const FirstStage&);	//�R�s�[�R���X�g���N�^

	Camera* camera;
	Light* light;
	BackGround* backGround;
	Player* player;
	Enemy* enemy;
	BallBullet* ballBullet;
	Wall* wall;
	HitChecker* hitChecker;
	FirstStageMap* firstStageMap;
	CakeRepopEffect* cakeEffect;
	UiManager* uiManager;
	FadeManager* fadeManager;

	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void UpdateGoal(float deltaTime);				//�S�[��
	void (FirstStage::* pUpdate)(float deltaTime);	//Update�֐��|�C���^

	State state;		//�Q�[�����
	int font;			//�Q�[���t�H���g
	int frame;

	//�ÓI�萔
	static const int GOAL_POSITION;					//�S�[���̈ʒu
};