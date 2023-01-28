#pragma once

#include "DxLib.h"
#include "Ball.h"
#include "Bullet.h"
#include "HitChecker.h"
#include "Cake_Repop_Effect.h"

class Cake_Repop_Effect;


/// <summary>
/// ボールとバレット管理クラス
/// </summary>
class BallBullet final
{
public:

    BallBullet(VECTOR ballPos);
    virtual ~BallBullet();

    void Update(float deltaTime, VECTOR playerPos, HitChecker* hitChecker, Cake_Repop_Effect* effect);     //更新処理
    void Activate();            //活性化処理
    void Finalize();            //終了処理

    void Draw();                //描画処理
    
    Ball* ball;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, VECTOR playerPos);          //バレット発射処理
    void BulletReuse(float deltaTime, Cake_Repop_Effect* effect);      //バレット再使用カウント

    float bulletCount;                                      //弾の効果時間
};