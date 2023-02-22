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
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePos);
    virtual ~CakeBullet();

    void Update(float deltaTime, const VECTOR& playerPos, 
                HitChecker* hitChecker, CakeRepopEffect* cakeEffect); //更新処理

    void Initialize();          //初期化処理
    void Activate();            //活性化処理
    void Finalize();            //終了処理
    void Draw();                //描画処理
    
    const bool CakeGet() { return cakeGet; }                        //ケーキを所持しているかいないかを返す

    Cake* cake;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, const VECTOR& playerPos);            //バレット発射処理
    void BulletReuse(float deltaTime, CakeRepopEffect* cakeEffect);  //バレット再使用カウント

    float bulletCount;                                               //弾の効果時間
    bool cakeGet;                                                    //ケーキを所持しているかいないか
    int	locateSe;				                                     //ケーキを置いた時のSE音格納用


    //定数
    const std::string SOUND_FOLDER_PATH;		//soundフォルダまでのパス
    const std::string LOCATE_SE_PATH;		    //ケーキを置いた時のSE音のパス

};