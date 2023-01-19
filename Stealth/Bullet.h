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

	void Initialize();
	void Activate();
	void Finalize();
	void Update(float deltaTime, Ball* ball);
	void MouseMove(Ball* ball, VECTOR playerPos);		//マウスカーソルの移動
	void SetDead();								//バレットを非アクティブ化
	void SetAlive();							//バレットをアクティブ化

	bool GetAlive() { return alive; }
	void Draw();
	
private:

	Bullet(const Bullet&);					//コピーコンストラクタ

	void OnShot(float deltaTime);			//球が撃たれた時

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