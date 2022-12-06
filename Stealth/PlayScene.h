#pragma once

#include "SceneBase.h"

class Player;
class Camera;

//�v���C�V�[���N���X
class PlayScene final : public SceneBase
{
public:
	 PlayScene();
	~PlayScene();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime);
	void Draw();

	//�Q�[�����
	enum State
	{
		START,	//�J�n�O
		GAME,	//�Q�[����
	};

private:
	PlayScene(const PlayScene&);		//�R�s�[�R���X�g���N�^

	Player* player;
	Camera* camera;

	void UpdateStart(float deltaTime);				//�Q�[���J�n�O
	void UpdateGame(float deltaTime);				//�Q�[����
	void (PlayScene::* pUpdate)(float deltaTime);

	State state;		//�Q�[�����
};