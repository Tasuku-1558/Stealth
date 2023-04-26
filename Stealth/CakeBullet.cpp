#include "CakeBullet.h"
#include "SoundManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cakePosition">ケーキの座標</param>
/// <param name="inEffect">エフェクトマネージャーのポインタ</param>
/// <param name="playerPosition">プレイヤーの座標</param>
CakeBullet::CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, VECTOR playerPosition)
    : bulletCount(0.0f)
    , cakeGet(false)
    , RESPAWN_EFFECT_POP_COUNT(5.7f)
    , MAX_BULLET_TIME(6.0f)
{
    cake = new Cake(cakePosition);
    bullet = new Bullet(playerPosition);

    effectManager = inEffect;
}

/// <summary>
/// デストラクタ
/// </summary>
CakeBullet::~CakeBullet()
{
    delete cake;
    delete bullet;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void CakeBullet::Update(float deltaTime)
{
    //ケーキが生きていないならば
    if (!cake->GetAlive())
    {
        cakeGet = true;
    }

    Shoot(deltaTime);
    BulletReuse(deltaTime);
}

/// <summary>
/// バレット発射処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void CakeBullet::Shoot(float deltaTime)
{
    //マウスカーソルを左クリックし、且つケーキとバレットが非アクティブならば
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !bullet->GetAlive() && !cake->GetAlive())
	{
        bullet->Update(deltaTime);
		bullet->BulletAlive();

        //ケーキを置いた時のSE音を再生
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

    bullet->MouseMove(cake->GetAlive());
}

/// <summary>
/// バレット再使用カウント
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void CakeBullet::BulletReuse(float deltaTime)
{
    //バレットが生きてるならば
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        cakeGet = false;

        if (bulletCount > RESPAWN_EFFECT_POP_COUNT)
        {
            //リスポーンエフェクトを出す
            effectManager->CreateEffect(cake->GetPosition(), EffectManager::RESPAWN);
        }

        //カウントが6秒経過したら
        if (bulletCount > MAX_BULLET_TIME)
        {
            //ケーキをアクティブ状態にし、バレットを非アクティブにする
            cake->CakeAlive();

            bullet->BulletDead();

            bulletCount = 0.0f;
        }
    }
}

/// <summary>
/// 描画処理
/// </summary>
void CakeBullet::Draw()
{
    //ケーキが生きてるならば
    if (cake->GetAlive())
    {
        cake->Draw();
    }

    bullet->Draw();
}