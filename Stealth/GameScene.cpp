#include "Json.h"
#include "GameScene.h"

#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "StageBlock.h"
#include "Player.h"
#include "Enemy.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "EffectManager.h"
#include "UiManager.h"
#include "FadeManager.h"
#include "StageData.h"
#include "Set.h"


//�f�o�b�N�p
#define DEBUG

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
	: SceneBase(SceneType::GAME)
	, gameState(GameState::START)
	, pUpdate(nullptr)
	, gameFontHandle(0)
	, stageNo(0)
	, gameStartCount(0.0f)
	, clear(true)
	, stagePos()
	, MAX_STAGE_NUMBER(2)
	, FIRST_STAGE_NUMBER(1)
	, SECOND_STAGE_NUMBER(2)
	, GAME_FONT_SIZE(50)
	, FONT_THICK(1)
	, PLAYER_HP(2)
	, MAX_GAME_START_COUNT(1.5f)
	, STAGE_POS_Y(-100.0f)
{
	GameData::doc.ParseStream(GameData::isw);

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	DeleteFontToHandle(gameFontHandle);
}

/// <summary>
/// ����������
/// </summary>
void GameScene::Initialize()
{
	camera = new Camera();

	light = new Light();
	
	backGround = new BackGround();

	effectManager = new EffectManager();

	player = new Player(effectManager);

	hitChecker = new HitChecker();

	stageNo = Set::GetInstance().GetStage();

	StageList stageList[] =
	{
		{FIRST_STAGE_NUMBER,  "Stage1", 2, 1},
		{SECOND_STAGE_NUMBER, "Stage2", 1, 1},
	};

	for (int i = 0; i < MAX_STAGE_NUMBER; i++)
	{
		if (stageNo == stageList[i].number)
		{
			stageData = new StageData();

			StagePop(stageData->s);

			goalFlag = new GoalFlag({ GameData::doc["GoalPosition"][stageList[i].name]["x"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["y"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["z"].GetFloat() });

			CakeBulletPop(stageList[i].number, stageList[i].name, stageList[i].cakeNumber);

			EnemyPop(stageList[i].number, stageList[i].name, stageList[i].enemyNumber);
		}
	}
	
	uiManager = new UiManager();

	fadeManager = new FadeManager();

	//�Q�[���t�H���g�̓ǂݍ���
	gameFontHandle = CreateFontToHandle("Oranienbaum", GAME_FONT_SIZE, FONT_THICK);

	pUpdate = &GameScene::UpdateStart;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
SceneType GameScene::Update(float deltaTime)
{
	if (pUpdate != nullptr)
	{
		(this->*pUpdate)(deltaTime);		//��Ԃ��ƂɍX�V
	}

	return nowSceneType;
}

/// <summary>
/// �X�e�[�W�̏o��
/// </summary>
/// <param name="stageData">�X�e�[�W�̃f�[�^</param>
void GameScene::StagePop(int stageData[BLOCK_NUM_Z][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_Z; i++)
	{
		for (int j = 0; j < BLOCK_NUM_X; j++)
		{
			stagePos.x = i * 300.0f;
			stagePos.z = j * -300.0f;

			if (stageData[j][i] == 0)
			{
				activeStage.emplace_back(new StageBlock(stagePos, { 1.0f,1.0f,1.0f }));
			}
		}
	}

	stagePos.y = STAGE_POS_Y;
}

/// <summary>
/// �P�[�L�o���b�g�̏o��
/// </summary>
/// <param name="number">�X�e�[�W�̔ԍ�</param>
/// <param name="stageName">�X�e�[�W�̖��O</param>
/// <param name="cakeNumber">�P�[�L�̐�</param>
void GameScene::CakeBulletPop(int number, char stageName[7], int cakeNumber)
{
	if (number == FIRST_STAGE_NUMBER)
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"][stageName]["1"]["x"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["y"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["z"].GetFloat() },

			{ GameData::doc["CakePosition"][stageName]["2"]["x"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["2"]["y"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["2"]["z"].GetFloat() }
		};
	}
	else
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"][stageName]["1"]["x"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["y"].GetFloat(),
			  GameData::doc["CakePosition"][stageName]["1"]["z"].GetFloat() },
		};
	}

	for (int i = 0; i < cakeNumber; i++)
	{
		activeCakeBullet.emplace_back(new CakeBullet(cakeBulletPosition[i], effectManager, player));
	}
}

/// <summary>
/// �G�l�~�[�̏o��
/// </summary>
/// <param name="number">�X�e�[�W�̔ԍ�</param>
/// <param name="stageName">�X�e�[�W�̖��O</param>
/// <param name="enemyNumber">�G�̐�</param>
void GameScene::EnemyPop(int number, char stageName[7], int enemyNumber)
{
	if (number == FIRST_STAGE_NUMBER)
	{
		enemyMovePattern =
		{
			{GameData::doc["EnemyMovePattern"][stageName].GetInt()},
		};

		enemySpeed =
		{
			{GameData::doc["EnemySpeed"][stageName].GetFloat()},
		};
	}
	else
	{
		enemyMovePattern =
		{
			{GameData::doc["EnemyMovePattern"][stageName].GetInt()},
		};

		enemySpeed =
		{
			{GameData::doc["EnemySpeed"][stageName].GetFloat()},
		};
	}

	for (int i = 0; i < enemyNumber; i++)
	{
		//�G�l�~�[�ɍs���p�^�[���̃i���o�[�ƃX�s�[�h��ݒ�
		activeEnemy.emplace_back(new Enemy(enemyMovePattern[i], enemySpeed[i]));
	}
}

/// <summary>
/// �V�[�������
/// </summary>
/// <param name="decision">�Q�[���N���A���Q�[���I�[�o�[��</param>
void GameScene::InputScene(bool decision)
{
	fadeManager->FadeMove();

	//�t�F�[�h���I�������
	if (fadeManager->FadeEnd())
	{
		Set::GetInstance().SetResult(decision);

		//���U���g��ʂ֑J��
		nowSceneType = SceneType::RESULT;
	}
}

/// <summary>
/// ��ʂ�ς���
/// </summary>
void GameScene::ChangeScreen()
{
	//�G�l�~�[��2�񌩂�������
	if (player->FindCount() == PLAYER_HP)
	{
		gameState = GameState::OVER;
		pUpdate = &GameScene::UpdateOver;
	}

	//�v���C���[���S�[���n�_�ɒH�蒅������
	if (hitChecker->GoalHit())
	{
		gameState = GameState::GOAL;
		pUpdate = &GameScene::UpdateGoal;
	}
}

/// <summary>
/// �Q�[���J�n�O
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateStart(float deltaTime)
{
	gameStartCount += deltaTime;

	backGround->Update();

	camera->Update(player->GetPosition());

	for (auto itr = activeEnemy.begin(); itr != activeEnemy.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}

	effectManager->CreateEffect(player->GetPosition(), EffectManager::RESPAWN);

	//1.5�b�o�߂�����Q�[����ʂֈڍs
	if (gameStartCount > MAX_GAME_START_COUNT)
	{
		gameState = GameState::GAME;
		pUpdate = &GameScene::UpdateGame;
	}
}

/// <summary>
/// �Q�[����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateGame(float deltaTime)
{
	backGround->Update();

	camera->Update(player->GetPosition());

	player->Update(deltaTime);

	for (auto itr = activeEnemy.begin(); itr != activeEnemy.end(); ++itr)
	{
		player->FoundEnemy(deltaTime, (*itr)->Spotted());

		(*itr)->Update(deltaTime);
	}

	for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}

	goalFlag->Update(deltaTime);

	hitChecker->Check(deltaTime, &activeStage, player, &activeCakeBullet, &activeEnemy, goalFlag);

	ChangeScreen();
}

/// <summary>
/// �S�[��
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateGoal(float deltaTime)
{
	InputScene(clear);
}

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void GameScene::UpdateOver(float deltaTime)
{
	InputScene(!clear);
}

/// <summary>
/// �`�揈��
/// </summary>
void GameScene::Draw()
{
	backGround->Draw();

	for (auto itr = activeStage.begin(); itr != activeStage.end(); ++itr)
	{
		(*itr)->Draw();
	}

	goalFlag->Draw();

	for (auto itr = activeEnemy.begin(); itr != activeEnemy.end(); ++itr)
	{
		(*itr)->Draw();
	}

	//�Q�[����Ԃ��X�^�[�g�ł͂Ȃ��Ȃ��
	if (gameState != GameState::START)
	{
		player->Draw();
		
		for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
		{
			(*itr)->Draw();

			uiManager->CakeGetDraw((*itr)->CakeGet());
		}
	}

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UiHit());
	
	fadeManager->Draw();

	//�f�o�b�N�p
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), gameFontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), gameFontHandle, "Z : %.0f", player->GetPosition().z);
#endif // DEBUG
}