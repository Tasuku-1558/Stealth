#include "Bullet.h"
#include "ModelManager.h"
#include "InputManager.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="inPlayer">プレイヤーのポインタ</param>
Bullet::Bullet(Player* const inPlayer)
	: cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, alive(false)
	, worldMouse()
	, RADIUS(50.0f)
	, SCALE(0.4)
	, ANGLE(0.0)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, POSITION({ 0.0f, 30.0f, 0.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, INITIAL_WORLD_MOUSE({ 0.0f,30.0f,0.0f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, CURSOR_PATH("pointer.png")
{
	Initialize();
	player = inPlayer;
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
	//ケーキモデルの読み込み
	modelHandle = ModelManager::GetInstance().GetModelHandle(ModelManager::CAKE);

	//ケーキモデルのサイズと回転値を設定
	MV1SetScale(modelHandle, SIZE);
	MV1SetRotationXYZ(modelHandle, ROTATE);

	//カーソル画像の読み込み
	cursorImage = LoadGraph(Input::InputPath(IMAGE_FOLDER_PATH, CURSOR_PATH).c_str());

	position = POSITION;

	worldMouse = INITIAL_WORLD_MOUSE;

	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = POSITION;
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
/// <param name="deltaTime">前フレームと現在のフレームの差分</param>
void Bullet::Update(float deltaTime)
{
	OnShot();

	//当たり判定球の移動処理
	collisionSphere.Move(position);
}

/// <summary>
/// マウスカーソルの移動
/// </summary>
/// <param name="cake">ケーキのポインタ</param>
void Bullet::MouseMove(Cake* cake)
{
	//マウスの座標取得
	GetMousePoint(&mouseX, &mouseY);
	mouseX -= 960;
	mouseY -= 540;

	//ケーキが死んだら
	if (!cake->GetAlive())
	{
		//マウスのX,Z座標のワールド座標を計算
		worldMouse.x = (float)mouseY * (-3000.0f / 1920.0f) * 1.7f + player->GetPosition().z;
		worldMouse.z = (float)mouseX * (1900.0f / 1080.0f) * 1.5f + player->GetPosition().x;
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
	position = VGet(worldMouse.z, worldMouse.y, worldMouse.x);

	//ケーキの位置を設定
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

	DrawRotaGraph(mouseX + 960, mouseY + 540, SCALE, ANGLE, cursorImage, TRUE);
}