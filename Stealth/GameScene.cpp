#include "Json.h"
#include "GameScene.h"
#include "DxLib.h"

#include "Camera.h"
#include "Light.h"
#include "BackGround.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "CakeBullet.h"
#include "GoalFlag.h"
#include "HitChecker.h"
#include "EffectManager.h"
#include "UiManager.h"
#include "FadeManager.h"
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
	, frame(0.0f)
	, clear(true)
	, MAX_STAGE_NUMBER(2)
	, FIRST_STAGE_NUMBER(1)
	, SECOND_STAGE_NUMBER(2)
	, GAME_FONT_SIZE(50)
	, FONT_THICK(1)
	, PLAYER_HP(2)
	, GAME_START_COUNT(1.3f)
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

	hitChecker = new HitChecker();

	player = new Player(effectManager);

	stageNo = Set::GetInstance().GetStage();

	StageList stageList[] =
	{
		{FIRST_STAGE_NUMBER,  "stage1", 2},
		{SECOND_STAGE_NUMBER, "stage2", 1},
	};

	for (int i = 0; i < MAX_STAGE_NUMBER; i++)
	{
		if (stageNo == stageList[i].number)
		{
			StagePop(StageData::stage1);

			//�G�l�~�[�ɍs���p�^�[���̃i���o�[�ƃX�s�[�h��ݒ�
			enemy = new Enemy(GameData::doc["EnemyMovePattern"][stageList[i].name].GetInt(), GameData::doc["EnemySpeed"][stageList[i].name].GetFloat());

			//�S�[���t���O�̏����ʒu��ݒ�
			goalFlag = new GoalFlag({ GameData::doc["GoalPosition"][stageList[i].name]["x"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["y"].GetFloat(),
									  GameData::doc["GoalPosition"][stageList[i].name]["z"].GetFloat() });

			CakeBulletPop(stageList[i].cakeNumber, stageList[i].number);

			EnemyPop(stageList[i].number);
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
void GameScene::StagePop(char stageData[BLOCK_NUM_Z][BLOCK_NUM_X])
{
	for (int i = 0; i < BLOCK_NUM_Z; i++)
	{
		for (int j = 0; j < BLOCK_NUM_X; j++)
		{
			float posX = i * 300.0f;
			float posZ = j * -300.0f;

			if (stageData[j][i] == 0)
			{
				activeStage.emplace_back(new Stage({ posX, STAGE_POS_Y, posZ }));
			}
		}
	}
}

/// <summary>
/// �P�[�L�o���b�g�̏o��
/// </summary>
/// <param name="cakeNumber">�P�[�L�̐�</param>
/// <param name="number">�X�e�[�W�̔ԍ�</param>
void GameScene::CakeBulletPop(int cakeNumber, int number)
{
	if (number == FIRST_STAGE_NUMBER)
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"]["stage1"]["x"].GetFloat(),
			  GameData::doc["CakePosition"]["stage1"]["y"].GetFloat(),
			  GameData::doc["CakePosition"]["stage1"]["z"].GetFloat() },

			{ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() }
		};
	}
	else
	{
		cakeBulletPosition =
		{
			{ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
			  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() },
		};
	}

	for (int i = 0; i < cakeNumber; i++)
	{
		if (stageNo == number)
		{
			activeCakeBullet.emplace_back(new CakeBullet(cakeBulletPosition[i], effectManager, player));
		}
	}
}

/// <summary>
/// �G�l�~�[�̏o��
/// </summary>
/// <param name="number">�X�e�[�W�̔ԍ�</param>
void GameScene::EnemyPop(int number)
{
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
	if (hitChecker->FlagHit())
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
	backGround->Update();

	camera->Update(player->GetPosition());

	enemy->Update(deltaTime, player->GetPosition());

	effectManager->CreateEffect(player->GetPosition(), EffectManager::RESPAWN);

	frame += deltaTime;

	//1.3�b�o�߂�����Q�[����ʂֈڍs
	if (frame > GAME_START_COUNT)
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

	player->Update(deltaTime, hitChecker->MapHit(), hitChecker->Back());

	player->FoundEnemy(deltaTime, enemy->Spotted());

	enemy->Update(deltaTime, player->GetPosition());

	for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
	{
		enemy->VisualAngleCake((*itr)->bullet->GetPosition(), deltaTime);

		//�G�l�~�[���P�[�L���������Ȃ��
		if (enemy->CakeFlag())
		{
			break;
		}
	}

	for (auto itr = activeCakeBullet.begin(); itr != activeCakeBullet.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}

	goalFlag->Update(deltaTime);

	hitChecker->Check(&activeStage, player, &activeCakeBullet, /*&enemy,*/ goalFlag);
	hitChecker->EnemyAndPlayer(player, enemy);

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

	enemy->Draw();

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

	goalFlag->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UiHit());
	
	fadeManager->Draw();

	//�f�o�b�N�p
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), gameFontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), gameFontHandle, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), gameFontHandle, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), gameFontHandle, "MapHit : %d", hitChecker->MapHit());
#endif // DEBUG
}