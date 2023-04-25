#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"
#include "Cake.h"
#include "Player.h"

using namespace std;

/// <summary>
/// ケーキ発射クラス
/// </summary>
class Bullet final : public ObjectBase
{
public:
	Bullet(Player* const inPlayer);
	virtual ~Bullet();

	void Update(float deltaTime);				//更新処理
	void Draw();								//描画処理

	void MouseMove(Cake* cake);					//マウスカーソルの移動
	void BulletDead();							//バレットを非アクティブ化
	void BulletAlive();							//バレットをアクティブ化

	const bool GetAlive() { return alive; }		//バレットが生きてるか死んでるかを返す
	
private:
	Bullet(const Bullet&);				//コピーコンストラクタ

	void Initialize();					//初期化処理
	void Finalize();					//終了処理
	void OnShot();						//球が撃たれた時

	int cursorImage;					//照準画像格納用
	int mouseX;							//マウスX座標
	int mouseY;							//マウスY座標
	bool alive;							//バレットが生きてるか死んでるか
	VECTOR worldMouse;					//ワールドマウス座標

	My3dLib::Sphere collisionSphere;	//当たり判定球

	Player* player;						//プレイヤーのポインタ

	//定数
	const float  RADIUS;				//ケーキの半径
	const double SCALE;					//カーソル画像の大きさ
	const double ANGLE;					//カーソル画像の回転値
	const VECTOR SIZE;					//モデルの倍率
	const VECTOR POSITION;				//モデルの位置
	const VECTOR ROTATE;				//モデルの回転値
	const VECTOR INITIAL_WORLD_MOUSE;	//初期のワールドマウス座標
	const string IMAGE_FOLDER_PATH;		//Imageフォルダまでのパス
	const string CURSOR_PATH;			//カーソル画像のパス
};