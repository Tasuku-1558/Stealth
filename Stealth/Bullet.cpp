#include "Bullet.h"
#include "ModelManager.h"
#include "Player.h"

using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
	: cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, worldMouseX(0.0f)
	, worldMouseY(30.0f)
	, worldMouseZ(0.0f)
	, alive(false)
	, IMAGE_FOLDER_PATH("Data/image/")
	, CURSOR_PATH("pointer.png")
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, POSITION({ 0.0f, 30.0f, 0.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, SCALE(0.4f)
	, RADIUS(50.0f)
{
	//処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{
	//処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Bullet::Initialize()
{
	//ケーキのモデルの読み込み
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE);

	//モデルのサイズと回転値を設定
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

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

	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = position;
	collisionSphere.radius = RADIUS;
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

	//当たり判定球の移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// マウスカーソルの移動
/// </summary>
/// <param name="cake"></param>
/// <param name="player">プレイヤーの位置</param>
void Bullet::MouseMove(Cake* cake, Player* player)
{
	//マウスの座標取得
	GetMousePoint(&mouseX, &mouseY);
	mouseX -= 960;
	mouseY -= 540;

	//ケーキが死んだら
	if (!cake->GetAlive())
	{
		//マウスのX,Z座標のワールド座標を計算
		worldMouseX = (float)mouseY * (3000.0f / -1920.0f) * 1.7f + player->GetPosition().z;
		worldMouseZ = (float)mouseX * (1900.0f / 1080.0f) * 1.5f + player->GetPosition().x;
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
	//モデルの位置を設定
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

	DrawRotaGraph(mouseX + 960, mouseY + 540, SCALE, 0.0f, cursorImage, TRUE);
}