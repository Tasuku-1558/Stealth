#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"

class CakeRepopEffect;

/// <summary>
/// �P�[�L�ƃo���b�g�Ǘ��N���X
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePos);
    virtual ~CakeBullet();

    void Update(float deltaTime, const VECTOR& playerPos, 
                HitChecker* hitChecker, CakeRepopEffect* cakeEffect); //�X�V����

    void Activate();            //����������
    void Finalize();            //�I������
    void Draw();                //�`�揈��
    
    Cake* cake;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, const VECTOR& playerPos);            //�o���b�g���ˏ���
    void BulletReuse(float deltaTime, CakeRepopEffect* cakeEffect);  //�o���b�g�Ďg�p�J�E���g

    float bulletCount;                                               //�e�̌��ʎ���
};