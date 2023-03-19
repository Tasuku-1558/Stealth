#include "CakeBullet.h"
#include "SoundManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cakePosition"></param>
/// <param name="inEffect"></param>
CakeBullet::CakeBullet(/*const VECTOR& cakePosition,*/ EffectManager* const inEffect)
    : bulletCount(0.0f)
    , cakeGet(false)
{
    //cake = new Cake(cakePosition);
    CakePop();
    bullet = new Bullet();

    effectManager = inEffect;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CakeBullet::~CakeBullet()
{
    //delete cake;
    for (auto cakePtr : cake)
    {
        DeleteCake(cakePtr);
    }

    delete bullet;
}

void CakeBullet::EntryCake(Cake* newCake)
{
    cake.emplace_back(newCake);
}

void CakeBullet::DeleteCake(Cake* deleteCake)
{
    //�P�[�L�o���b�g�I�u�W�F�N�g���猟�����č폜
	auto iter = std::find(cake.begin(), cake.end(), deleteCake);

	if (iter != cake.end())
	{
		//�P�[�L�o���b�g�I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
		std::iter_swap(iter, cake.end() - 1);
        cake.pop_back();

		return;
	}
}

void CakeBullet::CakePop()
{
    Cake* newCake = new Cake({ 0.0f,30.0f,0.0f });
    EntryCake(newCake);
    
    /*Cake* newCake2 = new Cake({ 200.0f,30.0f,0.0f });
    EntryCake(newCake2);*/
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void CakeBullet::Update(float deltaTime, Player* player)
{
    //�P�[�L�������Ă��Ȃ��Ȃ��
    for (auto cakePtr : cake)
    {
        if (!cakePtr->GetAlive())
        {
            cakeGet = true;
        }
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
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && cakeGet)
	{
        bullet->Update(deltaTime);
		bullet->BulletAlive();

        //�P�[�L��u��������SE�����Đ�
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

    for (auto cakePtr : cake)
    {
        bullet->MouseMove(cakePtr, player);
    }
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
            for (auto cakePtr : cake)
            {
                //���X�|�[���G�t�F�N�g���o��
                effectManager->CreateRepopEffect(cakePtr->GetPosition());
            }
        }

        //�J�E���g��6�b�ȏ�o�߂�����
        if (bulletCount > 6.0f)
        {
            //�P�[�L���A�N�e�B�u��Ԃɂ��A�o���b�g���A�N�e�B�u�ɂ���
            for (auto cakePtr : cake)
            {
                cakePtr->CakeAlive();
            }

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
    for (auto cakePtr : cake)
    {
        if (cakePtr->GetAlive())
        {
            cakePtr->Draw();
        }
    }

    bullet->Draw();
}