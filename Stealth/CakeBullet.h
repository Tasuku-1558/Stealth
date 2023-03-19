#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "EffectManager.h"
#include "Player.h"
#include <vector>

/// <summary>
/// ケーキとバレット管理クラス
/// ケーキが生きてるか死んでるか、ケーキを発射を管理
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(/*const VECTOR& cakePosition,*/ EffectManager* const inEffect);
    virtual ~CakeBullet();

    void Update(float deltaTime, Player* player);   //更新処理
    void Draw();                                    //描画処理
    
    const bool CakeGet() { return cakeGet; }        //ケーキを所持しているかいないかを返す
    std::vector<Cake*> cake;
    //Cake* cake;                                     //Cakeクラスのポインタ
    Bullet* bullet;                                 //Bulletクラスのポインタ
    EffectManager* effectManager;                   //EffectManagerクラスのポインタ

private:

    void Shoot(float deltaTime, Player* player);    //バレット発射処理
    void BulletReuse(float deltaTime);              //バレット再使用カウント
    void EntryCake(Cake* newCake);		//ケーキを登録
    void DeleteCake(Cake* deleteCake);	//ケーキを削除
    void CakePop();						//ケーキの出現


    float bulletCount;                              //弾の効果時間
    bool cakeGet;                                   //ケーキを所持しているかいないか

};