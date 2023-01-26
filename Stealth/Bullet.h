#pragma once

#include <string>

#include "ObjectBase.h"
#include "Math3D.h"
#include "Ball.h"

using namespace std;

/// <summary>
/// プレイヤーショットクラス
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet();
	 virtual ~Bullet();

	void Initialize();									//初期化処理
	void Activate();									//活性化処理
	void Finalize();									//終了処理
	void Update(float deltaTime);						//更新処理
	void MouseMove(Ball* ball, VECTOR playerPos);		//マウスカーソルの移動
	void BulletDead();									//バレットを非アクティブ化
	void BulletAlive();									//バレットをアクティブ化

	bool GetAlive() { return alive; }
	void Draw();										//描画処理
	
private:

	Bullet(const Bullet&);					//コピーコンストラクタ

	void OnShot();							//球が撃たれた時

	int cursorImage;						//照準画像格納用
	int mouseX;								//マウスX座標
	int mouseZ;								//マウスZ座標
	float worldMouseX;						//ワールドマウスX座標
	float worldMouseZ;						//ワールドマウスZ座標

	bool alive;								//生きてるか死んでるか

	//静的定数
	static const VECTOR SIZE;				//モデルの倍率
	static const VECTOR POSITION;			//モデルの位置
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string CURSOR_PATH;		//カーソル画像のパス
	static const float	SCALE;				//カーソル画像の大きさ
};