#include "CakeBullet.h"
#include "SoundManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cakePosition">�P�[�L�̍��W</param>
/// <param name="inEffect">�G�t�F�N�g�}�l�[�W���[�̃|�C���^</param>
/// <param name="inPlayer">�v���C���[�̃|�C���^</param>
CakeBullet::CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, Player* const inPlayer)
    : bulletCount(0.0f)
    , cakeGet(false)
    , RESPAWN_EFFECT_POP_TIME(5.7f)
    , MAX_BULLET_TIME(6.0f)
    , INITIAL_BULLET_TIME(0.0f)
{
    cake = new Cake(cakePosition);
    bullet = new Bullet();

    player = inPlayer;

    effectManager = inEffect;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CakeBullet::~CakeBullet()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�O�t���[���ƌ��݂̃t���[���̍���</param>
void CakeBullet::Update(float deltaTime)
{
    CakeViability();

    Shoot(deltaTime);

    BulletReuse(deltaTime);

    bullet->MouseMove(cake->GetAlive(), player->GetPosition());
}

/// <summary>
/// �P�[�L�̐���
/// </summary>
void CakeBullet::CakeViability()
{
    //�P�[�L�������Ă��Ȃ��Ȃ��
    if (!cake->GetAlive())
    {
        cakeGet = true;
    }
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

        if (bulletCount > RESPAWN_EFFECT_POP_TIME)
        {
            //���X�|�[���G�t�F�N�g���o��
            effectManager->CreateEffect(cake->GetPosition(), EffectManager::RESPAWN);
        }

        //�J�E���g��6�b�o�߂�����
        if (bulletCount > MAX_BULLET_TIME)
        {
            //�P�[�L���A�N�e�B�u��Ԃɂ��A�o���b�g���A�N�e�B�u��Ԃɂ���
            cake->CakeAlive();

            bullet->BulletDead();

            bulletCount = INITIAL_BULLET_TIME;
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