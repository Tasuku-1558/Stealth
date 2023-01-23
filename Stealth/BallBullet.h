#pragma once

#include "DxLib.h"
#include "Ball.h"
#include "Bullet.h"
#include "HitChecker.h"
#include "Effect.h"

class Effect;


/// <summary>
/// �{�[���ƃo���b�g�Ǘ��N���X
/// </summary>
class BallBullet final
{
public:

    BallBullet(VECTOR ballPos);
    virtual ~BallBullet();

    void Update(float deltaTime, VECTOR playerPos, HitChecker* hitChecker, Effect* effect);     //�X�V����
    void Activate();            //����������
    void Finalize();            //�I������

    void Draw();    //�`�揈��
    
    Ball* ball;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, VECTOR playerPos);          //�o���b�g���ˏ���
    void BulletReuse(float deltaTime, Effect* effect);      //�o���b�g�Ďg�p�J�E���g

    float bulletCount;          //�e�̌��ʎ���
};