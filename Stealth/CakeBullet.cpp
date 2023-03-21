#include "CakeBullet.h"
#include "SoundManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cakePosition"></param>
/// <param name="inEffect"></param>
CakeBullet::CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect)
    : bulletCount(0.0f)
    , cakeGet(false)
{
    cake = new Cake(cakePosition);
    bullet = new Bullet();

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
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void CakeBullet::Update(float deltaTime, Player* player)
{
    //ケーキが生きていないならば
    if (!cake->GetAlive())
    {
        cakeGet = true;
    }

    Shoot(deltaTime, player);
    BulletReuse(deltaTime);
}

/// <summary>
/// バレット発射処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void CakeBullet::Shoot(float deltaTime, Player* player)
{
    //マウスカーソルを左クリックし、且つケーキとバレットが非アクティブならば
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) && !bullet->GetAlive() && !cake->GetAlive())
	{
        bullet->Update(deltaTime);
		bullet->BulletAlive();

        //ケーキを置いた時のSE音を再生
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

    bullet->MouseMove(cake, player);
}

/// <summary>
/// バレット再使用カウント
/// </summary>
/// <param name="deltaTime"></param>
void CakeBullet::BulletReuse(float deltaTime)
{
    //バレットが生きてるならば
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        cakeGet = false;

        if (bulletCount > 5.7f)
        {
            //リスポーンエフェクトを出す
            effectManager->CreateRepopEffect(cake->GetPosition());
        }

        //カウントが6秒以上経過したら
        if (bulletCount > 6.0f)
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