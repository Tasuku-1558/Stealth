#include "BallBullet.h"
#include "Effect.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="ballPos"></param>
BallBullet::BallBullet(VECTOR ballPos)
    : ball(nullptr)
    , bullet(nullptr)
    , bulletCount(0)
{
    ball = new Ball(ballPos);
    bullet = new Bullet();

    ball->Initialize();
    bullet->Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BallBullet::~BallBullet()
{
    Finalize();
}

/// <summary>
/// ����������
/// </summary>
void BallBullet::Activate()
{
    bullet->Activate();
    ball->Activate();
}

/// <summary>
/// �I������
/// </summary>
void BallBullet::Finalize()
{
    ball->Finalize();
    bullet->Finalize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="hit"></param>
/// <param name="playerPos"></param>
/// <param name="hitChecker"></param>
/// <param name="effect"></param>
void BallBullet::Update(float deltaTime, VECTOR playerPos, HitChecker* hitChecker, Effect* effect)
{
    //�{�[���������Ă�Ȃ��
    if (ball->GetAlive())
    {
        hitChecker->BallAndPlayer(playerPos, ball);
        ball->IsAlive(hitChecker);
    }
    
    Shoot(deltaTime, playerPos);
    BulletReuse(deltaTime, effect);
}

/// <summary>
/// �o���b�g���ˏ���
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void BallBullet::Shoot(float deltaTime, VECTOR playerPos)
{
    //�}�E�X�J�[�\�������N���b�N���A���{�[���ƃo���b�g����A�N�e�B�u�Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !ball->GetAlive())
	{
		bullet->Update(deltaTime);
		bullet->BulletAlive();
	}

	bullet->MouseMove(ball, playerPos);
}

/// <summary>
/// �o���b�g�Ďg�p�J�E���g
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="effect"></param>
void BallBullet::BulletReuse(float deltaTime, Effect* effect)
{
    //�o���b�g�������Ă�Ȃ��
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        if (bulletCount > 4.7f)
        {
            //�{�[�������G�t�F�N�g���o��
            effect->Update(ball->GetPosition().x, ball->GetPosition().y, ball->GetPosition().z);
        }

        //�J�E���g��5�b�ȏ�o�߂�����
        if (bulletCount > 5.0f)
        {
            bulletCount = 0.0f;

            //�{�[�����A�N�e�B�u��Ԃɂ��A�o���b�g���A�N�e�B�u�ɂ���
            ball->BallAlive();
            bullet->BulletDead();
        }
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void BallBullet::Draw()
{
    //�{�[���������Ă�Ȃ��
    if (ball->GetAlive())
    {
        ball->Draw();
    }

    bullet->Draw();
}