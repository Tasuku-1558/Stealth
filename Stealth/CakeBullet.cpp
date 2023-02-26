#include "CakeBullet.h"
#include "RepopEffect.h"
#include "SoundManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cakePos"></param>
CakeBullet::CakeBullet(const VECTOR& cakePos)
    : cake(nullptr)
    , bullet(nullptr)
    , bulletCount(0.0f)
    , cakeGet(false)
{
    cake = new Cake(cakePos);
    bullet = new Bullet();

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

    bulletCount = 0.0f;
    cakeGet = false;
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
/// <param name="hit"></param>
/// <param name="playerPos"></param>
/// <param name="hitChecker"></param>
/// <param name="cakeEffect"></param>
void CakeBullet::Update(float deltaTime, const VECTOR& playerPos, HitChecker* hitChecker, RepopEffect* cakeEffect)
{
    //�P�[�L�������Ă�Ȃ��
    if (cake->GetAlive())
    {
        //���菈�����s��
        hitChecker->CakeAndPlayer(playerPos, cake);
        cake->IsAlive(hitChecker);
    }
    else
    {
        cakeGet = true;
    }

    
    Shoot(deltaTime, playerPos);
    BulletReuse(deltaTime, cakeEffect);
}

/// <summary>
/// �o���b�g���ˏ���
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void CakeBullet::Shoot(float deltaTime, const VECTOR& playerPos)
{
    //�}�E�X�J�[�\�������N���b�N���A���P�[�L�ƃo���b�g����A�N�e�B�u�Ȃ��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !cake->GetAlive())
	{
		bullet->Update(deltaTime);
		bullet->BulletAlive();

        //�P�[�L��u��������SE�����Đ�
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

	bullet->MouseMove(cake, playerPos);
}

/// <summary>
/// �o���b�g�Ďg�p�J�E���g
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="cakeEffect"></param>
void CakeBullet::BulletReuse(float deltaTime, RepopEffect* cakeEffect)
{
    //�o���b�g�������Ă�Ȃ��
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        cakeGet = false;

        if (bulletCount > 5.7f)
        {
            //�P�[�L�����G�t�F�N�g���o��
            cakeEffect->Update(cake->GetPosition());
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
void CakeBullet::Draw()
{
    //�P�[�L�������Ă�Ȃ��
    if (cake->GetAlive())
    {
        cake->Draw();
    }

    bullet->Draw();
}