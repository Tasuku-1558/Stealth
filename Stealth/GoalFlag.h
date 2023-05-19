#pragma once

#include <string>
#include "ObjectBase.h"
#include "Math3D.h"
#include "Collision.h"

using namespace std;

/// <summary>
/// ゴールオブジェクトクラス
/// </summary>
class GoalFlag final : public ObjectBase
{
public:
	GoalFlag(VECTOR goalPosition);
	virtual ~GoalFlag();

	void Update(float deltaTime);		//更新処理
	void Draw();						//描画処理

	const float GetCollideRadius() { return collisionSphere.radius; }		//当たり判定球の半径を返す

private:
	GoalFlag(const GoalFlag&);			//コピーコンストラクタ

	void Initialize();					//初期化処理
	void Finalize();					//終了処理

	int goalImage;						//ゴール文字の画像
	VECTOR rotate;						//モデルの回転
	My3dLib::Sphere collisionSphere;	//当たり判定球

	//定数
	const float  ROTATE_SPEED;			//モデルの回転スピード
	const float  RADIUS;				//ゴールフラグの半径
	const float  GOAL_CENTER_POSITION;	//ゴール文字の中心座標
	const float  GOAL_SIZE;				//ゴール文字の大きさ
	const float  GOAL_ANGLE;			//ゴール文字の回転値
	const VECTOR SIZE;					//モデルの倍率
	const string IMAGE_FOLDER_PATH;		//Imageフォルダまでのパス
	const string GOAL_PATH;				//ゴール文字の画像のパス
};