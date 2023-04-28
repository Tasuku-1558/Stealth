#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "Player.h"
#include "EffectManager.h"


/// <summary>
/// ケーキバレットクラス
/// ケーキが生きてるか死んでるか、ケーキを発射を管理
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, Player* const inPlayer);
    virtual ~CakeBullet();

    void Update(float deltaTime);                   //更新処理
    void Draw();                                    //描画処理
    
    const bool CakeGet() { return cakeGet; }        //ケーキを所持しているかいないかを返す

    Cake* cake;                                     //Cakeクラスのポインタ
    Bullet* bullet;                                 //Bulletクラスのポインタ

private:
    CakeBullet(const CakeBullet&);                  //コピーコンストラクタ

    void CakeViability();                           //ケーキの生死
    void Shoot(float deltaTime);                    //バレット発射処理
    void BulletReuse(float deltaTime);              //バレット再使用カウント

    Player* player;                                 //Playerクラスのポインタ
    EffectManager* effectManager;                   //EffectManagerクラスのポインタ

    float bulletCount;                              //弾の効果時間
    bool cakeGet;                                   //ケーキを所持しているかいないか

    //定数
    const float RESPAWN_EFFECT_POP_TIME;            //リスポーンエフェクトの出現時間
    const float MAX_BULLET_TIME;                    //弾の最大効果時間
    const float INITIAL_BULLET_TIME;                //初期の弾の効果時間

};