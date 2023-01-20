#include "BallBullet.h"


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

BallBullet::~BallBullet()
{
    Finalize();
}

void BallBullet::Activate()
{
    bullet->Activate();
}

void BallBullet::Finalize()
{
    ball->Finalize();
    bullet->Finalize();
}

void BallBullet::Update(float deltaTime, bool hit, VECTOR playerPos, HitChecker* hitChecker)
{
    hitChecker->BallAndPlayer(playerPos, ball->GetPosition());

    if (hit)
    {
        ball->IsAlive(hit);
    }


    Shoot(deltaTime, playerPos);
    BulletReuse(deltaTime);
}

void BallBullet::Shoot(float deltaTime, VECTOR playerPos)
{
    //�}�E�X�J�[�\�������N���b�N���A���{�[���ƃo���b�g����A�N�e�B�u�Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !ball->GetAlive())
	{
		bullet->Update(deltaTime, ball);
		bullet->SetAlive();
		
	}

	bullet->MouseMove(ball, playerPos);
}

/// <summary>
/// �o���b�g�Ďg�p�J�E���g
/// </summary>
/// <param name="deltaTime"></param>
void BallBullet::BulletReuse(float deltaTime)
{
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        //�J�E���g��5�b�ȏ�o�߂�����
        if (bulletCount > 5.0f)
        {
            bulletCount = 0.0f;

            ball->SetAlive();
            bullet->SetDead();
        }
    }
}

void BallBullet::Draw()
{
    if (ball->GetAlive())
    {
        ball->Draw();
    }

    bullet->Draw();
}