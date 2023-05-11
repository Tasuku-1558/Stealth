#include "Bullet.h"
#include "ModelManager.h"
#include "InputManager.h"


using namespace Math3d;		//VECTORの計算に使用

/// <summary>
/// コンストラクタ
/// </summary>
Bullet::Bullet()
	: cursorImage(0)
	, mouseX(0)
	, mouseY(0)
	, alive(false)
	, worldMouse()
	, SCREEN_WIDTH_HALF(960)
	, SCREEN_HEIGHT_HALF(540)
	, RADIUS(50.0f)
	, MOUSE_X_WIDTH(-3000.0f)
	, MOUSE_Z_HEIGHT(1900.0f)
	, MOUSE_X_ADJUSTMENT(1.7f)
	, MOUSE_Z_ADJUSTMENT(1.5f)
	, SCALE(0.4)
	, ANGLE(0.0)
	, SIZE({ 20.0f, 20.0f, 20.0f })
	, INITIAL_POSITION({ 0.0f, 30.0f, 0.0f })
	, ROTATE({ 0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f })
	, IMAGE_FOLDER_PATH("Data/Image/")
	, CURSOR_PATH("pointer.png")
{
	Initialize();
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

	//当たり判定球の情報設定
	collisionSphere.localCenter = ZERO_VECTOR;
	collisionSphere.worldCenter = INITIAL_POSITION;
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
/// <param name="alive">ケーキが生きているか死んでいるか</param>
/// <param name="playerPosition">プレイヤーの座標</param>
void Bullet::MouseMove(bool alive, VECTOR playerPosition)
{
	//マウスの座標取得
	GetMousePoint(&mouseX, &mouseY);
	mouseX -= SCREEN_WIDTH_HALF;
	mouseY -= SCREEN_HEIGHT_HALF;

	//ケーキが死んだら
	if (!alive)
	{
		//マウスのX、Z座標のワールド座標を計算
		worldMouse.x = (float)mouseY * (MOUSE_X_WIDTH / SCREEN_WIDTH) * MOUSE_X_ADJUSTMENT + playerPosition.z;
		worldMouse.z = (float)mouseX * (MOUSE_Z_HEIGHT / SCREEN_HEIGHT) * MOUSE_Z_ADJUSTMENT + playerPosition.x;
	}
}

/// <summary>
/// バレットを非アクティブ化
/// </summary>
void Bullet::BulletDead()
{
	alive = false;
	position = INITIAL_POSITION;
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
	position = { worldMouse.z, worldMouse.y, worldMouse.x };

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

	DrawRotaGraph(mouseX + SCREEN_WIDTH_HALF, mouseY + SCREEN_HEIGHT_HALF, SCALE, ANGLE, cursorImage, TRUE);
}