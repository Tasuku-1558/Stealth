#include "CakeBullet.h"
#include "SoundManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cakePosition">ケーキの座標</param>
/// <param name="inEffect">エフェクトマネージャーのポインタ</param>
/// <param name="inPlayer">プレイヤーのポインタ</param>
CakeBullet::CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, Player* const inPlayer)
    : bulletCount(0.0f)
    , cakeGet(false)
    , RESPAWN_EFFECT_POP_TIME(5.7f)
    , MAX_BULLET_TIME(6.0f)
    , INITIAL_BULLET_TIME(0.0f)
{
    cake = new Cake(cakePosition);
    bullet = new Bullet();

    player = inPlayer;

    effectManager = inEffect;
}

/// <summary>
/// デストラクタ
/// </summary>
CakeBullet::~CakeBullet()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void CakeBullet::Update(float deltaTime)
{
    CakeViability();

    Shoot(deltaTime);

    BulletReuse(deltaTime);

    bullet->MouseMove(cake->GetAlive(), player->GetPosition());
}

/// <summary>
/// ケーキの生死
/// </summary>
void CakeBullet::CakeViability()
{
    //ケーキが生きていないならば
    if (!cake->GetAlive())
    {
        cakeGet = true;
    }
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

        if (bulletCount > RESPAWN_EFFECT_POP_TIME)
        {
            //リスポーンエフェクトを出す
            effectManager->CreateEffect(cake->GetPosition(), EffectManager::RESPAWN);
        }

        //カウントが6秒経過したら
        if (bulletCount > MAX_BULLET_TIME)
        {
            //ケーキをアクティブ状態にし、バレットを非アクティブ状態にする
            cake->CakeAlive();

            bullet->BulletDead();

            bulletCount = INITIAL_BULLET_TIME;
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