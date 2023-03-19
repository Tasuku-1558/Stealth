#include "CakeBullet.h"
#include "SoundManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="cakePosition"></param>
/// <param name="inEffect"></param>
CakeBullet::CakeBullet(/*const VECTOR& cakePosition,*/ EffectManager* const inEffect)
    : bulletCount(0.0f)
    , cakeGet(false)
{
    //cake = new Cake(cakePosition);
    CakePop();
    bullet = new Bullet();

    effectManager = inEffect;
}

/// <summary>
/// デストラクタ
/// </summary>
CakeBullet::~CakeBullet()
{
    //delete cake;
    for (auto cakePtr : cake)
    {
        DeleteCake(cakePtr);
    }

    delete bullet;
}

void CakeBullet::EntryCake(Cake* newCake)
{
    cake.emplace_back(newCake);
}

void CakeBullet::DeleteCake(Cake* deleteCake)
{
    //ケーキバレットオブジェクトから検索して削除
	auto iter = std::find(cake.begin(), cake.end(), deleteCake);

	if (iter != cake.end())
	{
		//ケーキバレットオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, cake.end() - 1);
        cake.pop_back();

		return;
	}
}

void CakeBullet::CakePop()
{
    Cake* newCake = new Cake({ 0.0f,30.0f,0.0f });
    EntryCake(newCake);
    
    /*Cake* newCake2 = new Cake({ 200.0f,30.0f,0.0f });
    EntryCake(newCake2);*/
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="player"></param>
void CakeBullet::Update(float deltaTime, Player* player)
{
    //ケーキが生きていないならば
    for (auto cakePtr : cake)
    {
        if (!cakePtr->GetAlive())
        {
            cakeGet = true;
        }
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
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !bullet->GetAlive() && cakeGet)
	{
        bullet->Update(deltaTime);
		bullet->BulletAlive();

        //ケーキを置いた時のSE音を再生
        SoundManager::GetInstance().SePlayFlag(SoundManager::CAKE_SHOOT);
	}

    for (auto cakePtr : cake)
    {
        bullet->MouseMove(cakePtr, player);
    }
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
            for (auto cakePtr : cake)
            {
                //リスポーンエフェクトを出す
                effectManager->CreateRepopEffect(cakePtr->GetPosition());
            }
        }

        //カウントが6秒以上経過したら
        if (bulletCount > 6.0f)
        {
            //ケーキをアクティブ状態にし、バレットを非アクティブにする
            for (auto cakePtr : cake)
            {
                cakePtr->CakeAlive();
            }

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
    for (auto cakePtr : cake)
    {
        if (cakePtr->GetAlive())
        {
            cakePtr->Draw();
        }
    }

    bullet->Draw();
}