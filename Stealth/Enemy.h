#pragma once

#include <string>
#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"
#include "Map.h"
#include "Player.h"


/// <summary>
/// エネミーの状態
/// </summary>
enum class EnemyState
{
	CRAWL,			//巡回中
	ARRIVAL,		//目的地に到着
};


/// <summary>
/// エネミークラス
/// </summary>
class Enemy final : public EnemyBase
{
public:
	 Enemy(Map* map);		//コンストラクタ
	~Enemy();				//デストラクタ

	void Initialize();
	void Update(float deltaTime, Player* player);
	void Draw();

	bool Discovery() { return discovery; }

	//デバック用
	int GetPlayerCount() { return playerFindCount; }
	
	enum class EnemyState enemyState;

private:
	Enemy(const Enemy&);						//コピーコンストラクタ

	void Position(Map* map);					//エネミー位置設定
	bool IsGoal(float deltaTime);				//目的地に到達したならば
	void eUpdate(float deltaTime);				//状態変化
	void SetTargetPosition();					//移動処理
	void VisualAngle(Player* player);			//視野角の計算
	void Reaction(Object object);				//エネミーのオブジェクトごとの反応
	void Finalize();


	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	VECTOR targetPosition;			//目的地の座標
	Object object;					//オブジェクトのタグ

	const float length;				//視野角の距離
	bool discovery;					//発見

	int playerFindCount;			//プレイヤーを見つけた回数

	int findImage;					//見つかった画像格納用


	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string FIND_PATH;			//見つかった画像のパス

};