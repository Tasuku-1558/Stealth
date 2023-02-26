#include "CakeBullet.h"
#include "RepopEffect.h"
#include "SoundManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cakePos"></param>
CakeBullet::CakeBullet(const VECTOR& cakePos)
    : cake(nullptr)
    , bullet(nullptr)
    , bulletCount(0.0f)
    , cakeGet(false)
{
    cake = new Cake(cakePos);
    bullet = new Bullet();

    Initialize();
    Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
CakeBullet::~CakeBullet()
{
    Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void CakeBullet::Initialize()
{
    cake->Initialize();
    bullet->Initialize();
}

/// <summary>
/// 活性化処理
/// </summary>
void CakeBullet::Activate()
{
    cake->Activate();
    bullet->Activate();

    bulletCount = 0.0f;
    cakeGet = false;
}

/// <summary>
/// 終了処理
/// </summary>
void CakeBullet::Finalize()
{
    cake->Finalize();
    bullet->Finalize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="hit"></param>
/// <param name="playerPos"></param>
/// <param name="hitChecker"></param>
/// <param name="cakeEffect"></param>
void CakeBullet::Update(float deltaTime, const VECTOR& playerPos, HitChecker* hitChecker, RepopEffect* cakeEffect)
{
    //ケーキが生きてるならば
    if (cake->GetAlive())
    {
        //判定処理を行う
        hitChecker->CakeAndPlayer(playerPos, cake);
        cake->IsAlive(hitChecker);
    }
    else
    {
        cakeGet = true;
    }

    
    Shoot(deltaTime, playerPos);
    BulletReuse(deltaTime, cakeEffect);
}

/// <summary>
/// バレット発射処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void CakeBullet::Shoot(float deltaTime, const VECTOR& playerPos)
{
    //マウスカーソルを左クリックし、且つケーキとバレットが非アクティブならば
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !cake->GetAlive())
	{
		bullet->Update(deltaTime);
		bullet->BulletAlive();

        //ケーキを置いた時のSE音を再生
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

	bullet->MouseMove(cake, playerPos);
}

/// <summary>
/// バレット再使用カウント
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="cakeEffect"></param>
void CakeBullet::BulletReuse(float deltaTime, RepopEffect* cakeEffect)
{
    //バレットが生きてるならば
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        cakeGet = false;

        if (bulletCount > 5.7f)
        {
            //ケーキ復活エフェクトを出す
            cakeEffect->Update(cake->GetPosition());
        }

        //カウントが6秒以上経過したら
        if (bulletCount > 6.0f)
        {
            bulletCount = 0.0f;

            //ケーキをアクティブ状態にし、バレットを非アクティブにする
            cake->CakeAlive();
            bullet->BulletDead();
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