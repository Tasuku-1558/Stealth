#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"

class CakeRepopEffect;


/// <summary>
/// ケーキとバレット管理クラス
/// </summary>
class BallBullet final
{
public:

    BallBullet(VECTOR cakePos);
    virtual ~BallBullet();

    void Update(float deltaTime, VECTOR playerPos, 
                HitChecker* hitChecker, CakeRepopEffect* cakeEffect);     //更新処理

    void Activate();            //活性化処理
    void Finalize();            //終了処理
    void Draw();                //描画処理
    
    Cake* cake;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, VECTOR playerPos);                   //バレット発射処理
    void BulletReuse(float deltaTime, CakeRepopEffect* cakeEffect);  //バレット再使用カウント

    float bulletCount;                                               //弾の効果時間
};