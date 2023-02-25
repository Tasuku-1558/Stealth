#include "Bullet.h"
#include "ModelManager.h"


using namespace Math3d;

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet() : ObjectBase()
	, cursorImage(0)
	, mouseX(0)
	, mouseZ(0)
	, worldMouseX(0.0f)
	, worldMouseY(30.0f)
	, worldMouseZ(0.0f)
	, alive(false)
	, IMAGE_FOLDER_PATH("data/image/")
	, CURSOR_PATH("pointer.png")
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, POSITION({ 0.0f, 30.0f, 0.0f })
	, SCALE(0.4f)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{
	Finalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Bullet::Initialize()
{
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE);
	MV1SetScale(modelHandle, SIZE);

	//マウスカーソルを表示しない
	SetMouseDispFlag(FALSE);

	string failePath = IMAGE_FOLDER_PATH + CURSOR_PATH;
	cursorImage = LoadGraph(failePath.c_str());
}

/// <summary>
/// 活性化処理
/// </summary>
void Bullet::Activate()
{
	position = POSITION;

	BulletDead();
}

/// <summary>
/// 終了処理
/// </summary>
void Bullet::Finalize()
{
	MV1DeleteModel(modelHandle);

	DeleteGraph(cursorImage);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Bullet::Update(float deltaTime)
{
	OnShot();
}

/// <summary>
/// マウスカーソルの移動
/// </summary>
/// <param name="cake"></param>
/// <param name="playerPos"></param>
void Bullet::MouseMove(Cake* cake, VECTOR playerPos)
{
	GetMousePoint(&mouseX, &mouseZ);       //マウスの座標取得
	mouseX -= 960;
	mouseZ -= 540;

	//ケーキが死んだら
	if (!cake->GetAlive())
	{
		//マウスのX,Z座標のワールド座標を計算
		worldMouseX = (float)mouseX * (3000.0f / 1920.0f) * 1.6f + playerPos.z;
		worldMouseZ = (float)mouseZ * (1900.0f / 1080.0f) * 1.5f + playerPos.x;
	}
}

/// <summary>
/// バレットを非アクティブ化
/// </summary>
void Bullet::BulletDead()
{
	alive = false;
	position = POSITION;
}

/// <summary>
/// バレットをアクティブ化
/// </summary>
void Bullet::BulletAlive()
{
	alive = true;
}

/// <summary>
/// 球が撃たれた時
/// </summary>
void Bullet::OnShot()
{
	position = VGet(worldMouseZ, worldMouseY, worldMouseX);

	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画処理
/// </summary>
void Bullet::Draw()
{
	//ケーキが生きているなら
	if (alive)
	{
		MV1DrawModel(modelHandle);
	}

	DrawRotaGraph(mouseX + 960, mouseZ + 540, SCALE, 0.0f, cursorImage, TRUE);
}