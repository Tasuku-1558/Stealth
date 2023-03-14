#include "CakeBullet.h"
#include "Player.h"
#include "EffectManager.h"
#include "SoundManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cakePosition"></param>
/// <param name="inEffect"></param>
CakeBullet::CakeBullet(const VECTOR& cakePosition, EffectManager* inEffect)
    : bulletCount(0.0f)
    , cakeGet(false)
{
    cake = new Cake(cakePosition);
    bullet = new Bullet();

    effectManager = inEffect;

    Initialize();
    Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CakeBullet::~CakeBullet()
{
    Finalize();
}

/// <summary>
/// ����������
/// </summary>
void CakeBullet::Initialize()
{
    cake->Initialize();
    bullet->Initialize();
}

/// <summary>
/// ����������
/// </summary>
void CakeBullet::Activate()
{
    cake->Activate();
    bullet->Activate();
}

/// <summary>
/// �I������
/// </summary>
void CakeBullet::Finalize()
{
    cake->Finalize();
    bullet->Finalize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void CakeBullet::Update(float deltaTime, Player* player)
{
    //�P�[�L�������Ă��Ȃ��Ȃ��
    if (!cake->GetAlive())
    {
        cakeGet = true;
    }

    Shoot(deltaTime, player);
    BulletReuse(deltaTime);
}

/// <summary>
/// �o���b�g���ˏ���
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void CakeBullet::Shoot(float deltaTime, Player* player)
{
    //�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u�Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !cake->GetAlive())
	{
        bullet->Update(deltaTime);
		bullet->BulletAlive();

        //�P�[�L��u��������SE�����Đ�
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

	bullet->MouseMove(cake, player);
}

/// <summary>
/// �o���b�g�Ďg�p�J�E���g
/// </summary>
/// <param name="deltaTime"></param>
void CakeBullet::BulletReuse(float deltaTime)
{
    //�o���b�g�������Ă�Ȃ��
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        cakeGet = false;

        if (bulletCount > 5.7f)
        {
           //���X�|�[���G�t�F�N�g���o��
           effectManager->CreateRepopEffect(cake->GetPosition());
        }

        //�J�E���g��6�b�ȏ�o�߂�����
        if (bulletCount > 6.0f)
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