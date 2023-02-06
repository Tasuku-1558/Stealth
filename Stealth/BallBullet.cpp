#include "BallBullet.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cakePos"></param>
BallBullet::BallBullet(VECTOR cakePos)
    : cake(nullptr)
    , bullet(nullptr)
    , bulletCount(0)
{
    cake = new Cake(cakePos);
    bullet = new Bullet();

    cake->Initialize();
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
    cake->Activate();
    bullet->Activate();
}

/// <summary>
/// �I������
/// </summary>
void BallBullet::Finalize()
{
    cake->Finalize();
    bullet->Finalize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="hit"></param>
/// <param name="playerPos"></param>
/// <param name="hitChecker"></param>
/// <param name="cakeEffect"></param>
void BallBullet::Update(float deltaTime, VECTOR playerPos, HitChecker* hitChecker, CakeRepopEffect* cakeEffect)
{
    //�P�[�L�������Ă�Ȃ��
    if (cake->GetAlive())
    {
        hitChecker->BallAndPlayer(playerPos, cake);
        cake->IsAlive(hitChecker);
    }
    
    Shoot(deltaTime, playerPos);
    BulletReuse(deltaTime, cakeEffect);
}

/// <summary>
/// �o���b�g���ˏ���
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void BallBullet::Shoot(float deltaTime, VECTOR playerPos)
{
    //�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u�Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !cake->GetAlive())
	{
		bullet->Update(deltaTime);
		bullet->BulletAlive();
	}

	bullet->MouseMove(cake, playerPos);
}

/// <summary>
/// �o���b�g�Ďg�p�J�E���g
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="cakeEffect"></param>
void BallBullet::BulletReuse(float deltaTime, CakeRepopEffect* cakeEffect)
{
    //�o���b�g�������Ă�Ȃ��
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        if (bulletCount > 5.7f)
        {
            //�P�[�L�����G�t�F�N�g���o��
            cakeEffect->Update(cake->GetPosition().x, cake->GetPosition().y, cake->GetPosition().z);
        }

        //�J�E���g��6�b�ȏ�o�߂�����
        if (bulletCount > 6.0f)
        {
            bulletCount = 0.0f;

            //�P�[�L���A�N�e�B�u��Ԃɂ��A�o���b�g���A�N�e�B�u�ɂ���
            cake->CakeAlive();
            bullet->BulletDead();
        }
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void BallBullet::Draw()
{
    //�P�[�L�������Ă�Ȃ��
    if (cake->GetAlive())
    {
        cake->Draw();
    }

    bullet->Draw();
}