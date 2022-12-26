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
	 Bullet();
	~Bullet();

	void Initialize();
	void Finalize();
	void Activate(VECTOR inPosition, VECTOR inDir);
	void Update(float deltaTime, Boal* boal);
	void Draw();


private:

	void Move();							//マウスカーソル移動
	void OnShot(float deltaTime);			//球が撃たれた時

	int cursorImage;
	VECTOR cursorPosition;
	int mouseX;
	int mouseY;

	//静的定数
	static const VECTOR SIZE;           //モデルの倍率
	static const float  SPEED;			//モデルのスピード
	static const VECTOR COURSOR_POSITION;
	static const string IMAGE_FOLDER_PATH;		//imageフォルダまでのパス
	static const string CURSOR_PATH;		//カーソル画像のパス


};