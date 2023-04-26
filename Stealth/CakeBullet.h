#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "EffectManager.h"


/// <summary>
/// ケーキバレットクラス
/// ケーキが生きてるか死んでるか、ケーキを発射を管理
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, VECTOR playerPosition);
    virtual ~CakeBullet();

    void Update(float deltaTime);                   //更新処理
    void Draw();                                    //描画処理
    
    const bool CakeGet() { return cakeGet; }        //ケーキを所持しているかいないかを返す

    Cake* cake;                                     //Cakeクラスのポインタ
    Bullet* bullet;                                 //Bulletクラスのポインタ

private:

    void Shoot(float deltaTime);                    //バレット発射処理
    void BulletReuse(float deltaTime);              //バレット再使用カウント

    EffectManager* effectManager;                   //EffectManagerクラスのポインタ

    float bulletCount;                              //弾の効果時間
    bool cakeGet;                                   //ケーキを所持しているかいないか

    //定数
    const float RESPAWN_EFFECT_POP_COUNT;           //リスポーンエフェクト出現カウント
    const float MAX_BULLET_TIME;                   //弾の最大効果時間

};