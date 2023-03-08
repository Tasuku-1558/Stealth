#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "RepopEffect.h"

class Player;
class RepopEffect;

/// <summary>
/// ケーキとバレット管理クラス
/// ケーキが生きてるか死んでるか、ケーキを発射を管理
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePos);
    virtual ~CakeBullet();

    void Update(float deltaTime, Player* player,
                RepopEffect* cakeEffect);           //更新処理

    void Draw();                                    //描画処理
    
    const bool CakeGet() { return cakeGet; }                      //ケーキを所持しているかいないかを返す

    Cake* cake;         //Cakeクラスのポインタ
    Bullet* bullet;     //Bulletクラスのポインタ

private:

    void Initialize();                                               //初期化処理
    void Activate();                                                 //活性化処理
    void Finalize();                                                 //終了処理
    void Shoot(float deltaTime, Player* player);                     //バレット発射処理
    void BulletReuse(float deltaTime, RepopEffect* cakeEffect);      //バレット再使用カウント

    float bulletCount;                                               //弾の効果時間
    bool cakeGet;                                                    //ケーキを所持しているかいないか

};