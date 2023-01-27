#include "BallBullet.h"
#include "Effect.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="ballPos"></param>
BallBullet::BallBullet(VECTOR ballPos)
    : ball(nullptr)
    , bullet(nullptr)
    , bulletCount(0)
{
    ball = new Ball(ballPos);
    bullet = new Bullet();

    ball->Initialize();
    bullet->Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
BallBullet::~BallBullet()
{
    Finalize();
}

/// <summary>
/// 活性化処理
/// </summary>
void BallBullet::Activate()
{
    bullet->Activate();
    ball->Activate();
}

/// <summary>
/// 終了処理
/// </summary>
void BallBullet::Finalize()
{
    ball->Finalize();
    bullet->Finalize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="hit"></param>
/// <param name="playerPos"></param>
/// <param name="hitChecker"></param>
/// <param name="effect"></param>
void BallBullet::Update(float deltaTime, VECTOR playerPos, HitChecker* hitChecker, Effect* effect)
{
    //ボールが生きてるならば
    if (ball->GetAlive())
    {
        hitChecker->BallAndPlayer(playerPos, ball);
        ball->IsAlive(hitChecker);
    }
    
    Shoot(deltaTime, playerPos);
    BulletReuse(deltaTime, effect);
}

/// <summary>
/// バレット発射処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="playerPos"></param>
void BallBullet::Shoot(float deltaTime, VECTOR playerPos)
{
    //マウスカーソルを左クリックし、且つボールとバレットが非アクティブならば
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && !ball->GetAlive())
	{
		bullet->Update(deltaTime);
		bullet->BulletAlive();
	}

	bullet->MouseMove(ball, playerPos);
}

/// <summary>
/// バレット再使用カウント
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="effect"></param>
void BallBullet::BulletReuse(float deltaTime, Effect* effect)
{
    //バレットが生きてるならば
    if (bullet->GetAlive())
    {
        bulletCount += deltaTime;

        if (bulletCount > 4.7f)
        {
            //ボール復活エフェクトを出す
            effect->Update(ball->GetPosition().x, ball->GetPosition().y, ball->GetPosition().z);
        }

        //カウントが5秒以上経過したら
        if (bulletCount > 5.0f)
        {
            bulletCount = 0.0f;

            //ボールをアクティブ状態にし、バレットを非アクティブにする
            ball->BallAlive();
            bullet->BulletDead();
        }
    }
}

/// <summary>
/// 描画処理
/// </summary>
void BallBullet::Draw()
{
    //ボールが生きてるならば
    if (ball->GetAlive())
    {
        ball->Draw();
    }

    bullet->Draw();
}