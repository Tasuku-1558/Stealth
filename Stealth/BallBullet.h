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

    void Update(float deltaTime, VECTOR playerPos, HitChecker* hitChecker, Effect* effect);
    void Activate();
    void Finalize();

    void Draw(bool ballHit);
    
    Ball* ball;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, VECTOR playerPos);
    void BulletReuse(float deltaTime, Effect* effect);

    float bulletCount;          //�e�̌��ʎ���
};