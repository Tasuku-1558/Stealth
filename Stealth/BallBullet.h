#pragma once

#include "DxLib.h"
#include "Ball.h"
#include "Bullet.h"
#include "HitChecker.h"


/// <summary>
/// �{�[���ƃo���b�g�Ǘ��N���X
/// </summary>
class BallBullet final
{
public:

    BallBullet(VECTOR ballPos);
    virtual ~BallBullet();

    void Update(float deltaTime, bool hit, VECTOR playerPos, HitChecker* hitChecker);
    void Activate();
    void Finalize();

    void Draw();
    
    Ball* ball;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, VECTOR playerPos);
    void BulletReuse(float deltaTime);

    float bulletCount;          //�e�̌��ʎ���
};