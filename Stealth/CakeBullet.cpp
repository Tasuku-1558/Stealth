#include "CakeBullet.h"
#include "SoundManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cakePosition">�P�[�L�̍��W</param>
/// <param name="inEffect">�G�t�F�N�g�}�l�[�W���[�̃|�C���^</param>
/// <param name="playerPosition">�v���C���[�̍��W</param>
CakeBullet::CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, VECTOR playerPosition)
    : bulletCount(0.0f)
    , cakeGet(false)
    , RESPAWN_EFFECT_POP_COUNT(5.7f)
    , MAX_BULLET_TIME(6.0f)
{
    cake = new Cake(cakePosition);
    bullet = new Bullet(playerPosition);

    effectManager = inEffect;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CakeBullet::~CakeBullet()
{
    delete cake;
    delete bullet;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void CakeBullet::Update(float deltaTime)
{
    //�P�[�L�������Ă��Ȃ��Ȃ��
    if (!cake->GetAlive())
    {
        cakeGet = true;
    }

    Shoot(deltaTime);
    BulletReuse(deltaTime);
}

/// <summary>
/// �o���b�g���ˏ���
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void CakeBullet::Shoot(float deltaTime)
{
    //�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u�Ȃ��
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !bullet->GetAlive() && !cake->GetAlive())
	{
        bullet->Update(deltaTime);
		bullet->BulletAlive();

        //�P�[�L��u��������SE�����Đ�
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

    bullet->MouseMove(cake->GetAlive());
}

/// <summary>
/// �o���b�g�Ďg�p�J�E���g
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void CakeBullet::BulletReuse(float deltaTime)
{
    //�o���b�g�������Ă�Ȃ��
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        cakeGet = false;

        if (bulletCount > RESPAWN_EFFECT_POP_COUNT)
        {
            //���X�|�[���G�t�F�N�g���o��
            effectManager->CreateEffect(cake->GetPosition(), EffectManager::RESPAWN);
        }

        //�J�E���g��6�b�o�߂�����
        if (bulletCount > MAX_BULLET_TIME)
        {
            //�P�[�L���A�N�e�B�u��Ԃɂ��A�o���b�g���A�N�e�B�u�ɂ���
            cake->CakeAlive();

            bullet->BulletDead();

            bulletCount = 0.0f;
        }
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void CakeBullet::Draw()
{
    //�P�[�L�������Ă�Ȃ��
    if (cake->GetAlive())
    {
        cake->Draw();
    }

    bullet->Draw();
}