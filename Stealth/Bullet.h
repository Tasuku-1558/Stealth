#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"
#include "Cake.h"

class Player;

using namespace std;

/// <summary>
/// ケーキ発射クラス
/// </summary>
class Bullet final : public ObjectBase
{
public:
	Bullet();
	virtual ~Bullet();

	void Update(float deltaTime);						//更新処理
	void Draw();										//描画処理

	void MouseMove(Cake* cake, Player* player);			//マウスカーソルの移動
	void BulletDead();									//バレットを非アクティブ化
	void BulletAlive();									//バレットをアクティブ化

	const bool GetAlive() { return alive; }				//バレットが生きてるか死んでるかを返す
	
private:
	Bullet(const Bullet&);					//コピーコンストラクタ

	void Initialize();						//初期化処理
	void Activate();						//活性化処理
	void Finalize();						//終了処理
	void OnShot();							//球が撃たれた時

	int cursorImage;						//照準画像格納用
	int mouseX;								//マウスX座標
	int mouseY;								//マウスY座標
	float worldMouseX;						//ワールドマウスX座標
	float worldMouseY;						//ワールドマウスY座標
	float worldMouseZ;						//ワールドマウスZ座標
	bool alive;								//バレットが生きてるか死んでるか

	My3dLib::Sphere collisionSphere;		//当たり判定球

	//定数
	const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	const string CURSOR_PATH;		//カーソル画像のパス
	const VECTOR SIZE;				//モデルの倍率
	const VECTOR POSITION;			//モデルの位置
	const VECTOR ROTATE;			//モデルの回転値
	const float	 SCALE;				//カーソル画像の大きさ
	const float  RADIUS;			//ケーキの半径
};