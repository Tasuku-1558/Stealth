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
#include "CakeParticle.h"
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
	, particleFlag(false)
	, particleInterval(0.0f)
	, clear(true)
	, FIRST_STAGE_NUMBER(1)
	, SECOND_STAGE_NUMBER(2)
	, GAME_FONT_SIZE(50)
	, FONT_THICK(1)
	, PARTICLE_NUMBER(500)
	, PLAYER_HP(2)
	, GAME_START_COUNT(1.3f)
	, MAX_PARTICLE_INTERVAL(5.0f)
	, PARTICLE_INTERVAL(0.0f)
	, STAGE_POS_Y(0.0f)
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

	for (auto CakeBulletPtr : cakeBullet)
	{
		DeleteCakeBullet(CakeBulletPtr);
	}
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

	player = new Player(effectManager, hitChecker);

	stageNo = Set::GetInstance().GetStage();

	S stage[] =
	{
		{FIRST_STAGE_NUMBER,"stage1"},
		{SECOND_STAGE_NUMBER, "stage2"},
	};

	for (int i = 0; i < 2; i++)
	{
		if (stageNo == stage[i].number)
		{
			StagePop(StageData::stage1);

			//�G�l�~�[�ɍs���p�^�[���̃i���o�[�ƃX�s�[�h��ݒ�
			enemy = new Enemy(GameData::doc["EnemyMovePattern"][stage[i].name].GetInt(), GameData::doc["EnemySpeed"][stage[i].name].GetFloat());

			//�S�[���t���O�̏����ʒu��ݒ�
			goalFlag = new GoalFlag({ GameData::doc["GoalPosition"][stage[i].name]["x"].GetFloat(),
									  GameData::doc["GoalPosition"][stage[i].name]["y"].GetFloat(),
									  GameData::doc["GoalPosition"][stage[i].name]["z"].GetFloat() });

			CakeBulletPop(stage[i].number);

			EnemyPop(stage[i].number);
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
/// �X�e�[�W��o�^
/// </summary>
/// <param name="newStage">�o�^����X�e�[�W�̃|�C���^</param>
void GameScene::EntryStage(Stage* newStage)
{
	stage.emplace_back(newStage);
}

/// <summary>
/// �X�e�[�W�̍폜
/// </summary>
/// <param name="deleteStage">�폜����X�e�[�W�̃|�C���^</param>
void GameScene::DeleteStage(Stage* deleteStage)
{
	//�X�e�[�W�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(stage.begin(), stage.end(), deleteStage);

	if (iter != stage.end())
	{
		//�X�e�[�W�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, stage.end() - 1);
		stage.pop_back();

		return;
	}
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
			float posX = (j * 300.0f) + 50.0f;
			float posZ = (i * 300.0f) + 50.0f;

			if (stageData[j][i] == 0)
			{
				Stage* newStage = new Stage({ posX, STAGE_POS_Y, posZ });
				EntryStage(newStage);
			}
		}
	}
}

/// <summary>
/// �P�[�L�o���b�g��o�^
/// </summary>
/// <param name="newCakeBullet">�o�^����P�[�L�o���b�g�̃|�C���^</param>
void GameScene::EntryCakeBullet(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

/// <summary>
/// �P�[�L�o���b�g�̍폜
/// </summary>
/// <param name="deleteCakeBullet">�폜����P�[�L�o���b�g�̃|�C���^</param>
void GameScene::DeleteCakeBullet(CakeBullet* deleteCakeBullet)
{
	//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(cakeBullet.begin(), cakeBullet.end(), deleteCakeBullet);

	if (iter != cakeBullet.end())
	{
		//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, cakeBullet.end() - 1);
		cakeBullet.pop_back();

		return;
	}
}

/// <summary>
/// �P�[�L�o���b�g�̏o��
/// </summary>
/// <param name="number">�X�e�[�W�̔ԍ�</param>
void GameScene::CakeBulletPop(int number)
{
	if (number == FIRST_STAGE_NUMBER)
	{
		CakeBullet* newCakeBullet = new CakeBullet({ GameData::doc["CakePosition"]["stage1"]["x"].GetFloat(),
													 GameData::doc["CakePosition"]["stage1"]["y"].GetFloat(),
													 GameData::doc["CakePosition"]["stage1"]["z"].GetFloat() }, effectManager, player);
		EntryCakeBullet(newCakeBullet);

		CakeBullet* newCakeBullet2 = new CakeBullet({ GameData::doc["CakePosition"]["stage2"]["x"].GetFloat(),
													  GameData::doc["CakePosition"]["stage2"]["y"].GetFloat(),
													  GameData::doc["CakePosition"]["stage2"]["z"].GetFloat() }, effectManager, player);
		EntryCakeBullet(newCakeBullet2);
	}
}

/// <summary>
/// �G�l�~�[��o�^
/// </summary>
/// <param name="newEnemy">�o�^����G�l�~�[�̃|�C���^</param>
void GameScene::EntryEnemy(Enemy* newEnemy)
{
}

/// <summary>
/// �G�l�~�[�̍폜
/// </summary>
/// <param name="deleteEnemy">�폜����G�l�~�[�̃|�C���^</param>
void GameScene::DeleteEnemy(Enemy* deleteEnemy)
{
}

/// <summary>
/// �G�l�~�[�̏o��
/// </summary>
/// <param name="number">�X�e�[�W�̔ԍ�</param>
void GameScene::EnemyPop(int number)
{
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N����o�^
/// </summary>
/// <param name="newCakeParticle">�o�^����P�[�L�p�[�e�B�N���̃|�C���^</param>
void GameScene::EntryCakeParticle(CakeParticle* newCakeParticle)
{
	cakeParticle.emplace_back(newCakeParticle);
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N�����폜
/// </summary>
/// <param name="deleteCakeParticle">�폜����P�[�L�p�[�e�B�N���̃|�C���^</param>
void GameScene::DeleteCakeParticle(CakeParticle* deleteCakeParticle)
{
	//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(cakeParticle.begin(), cakeParticle.end(), deleteCakeParticle);

	if (iter != cakeParticle.end())
	{
		//�P�[�L�̃p�[�e�B�N���I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, cakeParticle.end() - 1);
		cakeParticle.pop_back();

		return;
	}
}

/// <summary>
/// �P�[�L�̃p�[�e�B�N���̏o��
/// </summary>
void GameScene::CakeParticlePop()
{
	for (auto CakeBulletPtr : cakeBullet)
	{
		//�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u���p�[�e�B�N�����o�Ă��Ȃ��Ȃ��
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && CakeBulletPtr->bullet->GetAlive() && !CakeBulletPtr->cake->GetAlive() && !particleFlag)
		{
			//�p�[�e�B�N���̌����G���g���[����
			for (int i = 0; i < PARTICLE_NUMBER; i++)
			{
				CakeParticle* newCakeParticle = new CakeParticle(CakeBulletPtr->bullet->GetPosition());
				EntryCakeParticle(newCakeParticle);
			}

			particleFlag = true;
		}
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

	enemy->Update(deltaTime, player);

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

	player->Update(deltaTime);

	player->FoundEnemy(deltaTime, enemy->Spotted());

	enemy->Update(deltaTime, player);

	for (auto CakeBulletPtr : cakeBullet)
	{
		enemy->VisualAngleCake(CakeBulletPtr->bullet, deltaTime);
		
		//�G�l�~�[���P�[�L���������Ȃ��
		if (enemy->CakeFlag())
		{
			break;
		}
	}

	for (auto CakeBulletPtr : cakeBullet)
	{
		CakeBulletPtr->Update(deltaTime);
	}

	goalFlag->Update(deltaTime);

	//�P�[�L�̃p�[�e�B�N���o��
	CakeParticlePop();

	//�p�[�e�B�N�����o������
	if (particleFlag)
	{
		particleInterval += deltaTime;

		//5�b�o�߂�����
		//�p�[�e�B�N�����ēx�o����悤�ɂ���
		if (particleInterval > MAX_PARTICLE_INTERVAL)
		{
			particleFlag = false;
			particleInterval = PARTICLE_INTERVAL;
		}
	}
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Update(deltaTime);
	}

	hitChecker->Check(&stage, player, &cakeBullet, /*&enemy,*/ goalFlag);
	hitChecker->EnemyAndPlayer(player, enemy);

	ChangeScreen();

	for (auto particlePtr : cakeParticle)
	{
		//�p�[�e�B�N�����o���I�������
		if (particlePtr->IsParticleEnd())
		{
			DeleteCakeParticle(particlePtr);
		}
	}
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

	for (auto StagePtr : stage)
	{
		StagePtr->Draw();
	}

	enemy->Draw();

	//�Q�[����Ԃ��X�^�[�g�ł͂Ȃ��Ȃ��
	if (gameState != GameState::START)
	{
		player->Draw();
		
		for (auto CakeBulletPtr : cakeBullet)
		{
			CakeBulletPtr->Draw();

			uiManager->CakeGetDraw(CakeBulletPtr->CakeGet());
		}
	}

	goalFlag->Draw();

	effectManager->Draw();

	uiManager->Draw(gameState, player->FindCount(), hitChecker->UiHit());
	
	for (auto particlePtr : cakeParticle)
	{
		particlePtr->Draw();
	}

	fadeManager->Draw();

	//�f�o�b�N�p
#ifdef DEBUG
	DrawFormatStringToHandle(100, 100, GetColor(255, 0, 0), gameFontHandle, "X : %.0f", player->GetPosition().x);
	DrawFormatStringToHandle(100, 150, GetColor(255, 0, 0), gameFontHandle, "Z : %.0f", player->GetPosition().z);
	DrawFormatStringToHandle(100, 200, GetColor(255, 0, 0), gameFontHandle, "PlayerCount : %d", player->FindCount());
	DrawFormatStringToHandle(100, 250, GetColor(255, 0, 0), gameFontHandle, "ParticleSize : %d", cakeParticle.size());
#endif // DEBUG
}