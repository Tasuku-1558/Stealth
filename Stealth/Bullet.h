#pragma once

#include "ObjectBase.h"
#include "Math3D.h"
#include <string>

using namespace std;

class Boal;

/// <summary>
/// プレイヤーショットクラス
/// </summary>
class Bullet final : public ObjectBase
{
public:
	 Bullet(Object BOAL);
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate();
	void Update(float deltaTime, Boal* boal);
	void MouseMove(Boal* boal);							//マウスカーソルの移動

	void Draw();

	//デバック用
	int GetMX() { return mouseX; }
	int GetMY() { return mouseY; }

private:

	void OnShot(float deltaTime);			//球が撃たれた時

	int cursorImage;						//照準画像格納用
	int mouseX;								//マウスX座標
	int mouseY;								//マウスY座標

	//静的定数
	static const VECTOR SIZE;				//モデルの倍率
	static const float  SPEED;				//モデルのスピード
	static const string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const string CURSOR_PATH;		//カーソル画像のパス

};