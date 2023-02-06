#pragma once

#include <vector>
#include <string>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;


/// <summary>
/// 監視エネミークラス
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(std::vector<VECTOR>& id);
	virtual ~MonitoringEnemy();

	void Initialize();									//初期化処理
	void Activate();									//活性化処理
	void Update(float deltaTime, Player* player);		//更新処理
	void Draw();										//描画処理

	void VisualAngleCake(Bullet* bullet, float deltaTime);	//エネミーの視野にケーキが入った場合
	void VisualAngleWall(VECTOR wallPos);					//エネミーの視野に壁が入った場合

	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す

	//エネミーの状態
	enum class EnemyState
	{
		CRAWL,			//巡回中
		ARRIVAL,		//目的地に到着
	};

private:
	MonitoringEnemy(const MonitoringEnemy&);						//コピーコンストラクタ

	void Position(std::vector<VECTOR>& id);		//エネミー位置設定
	bool IsGoal(float deltaTime);				//目的地に到達したならば
	void eUpdate(float deltaTime);				//エネミーの状態変化
	void SetTargetPosition();					//目的地まで移動処理
	void VisualAnglePlayer(Player* player);		//エネミーの視野にプレイヤーが入った場合

	void Reaction();							//エネミーのオブジェクトごとの反応
	void CakeEatCount(float deltaTime);			//秒数によってケーキの状態変化
	void ReactionDraw();						//リアクション画像の描画処理
	void Finalize();							//終了処理

	std::string InputPath(std::string folderPath, //画像のパスを入力
		std::string imagePath);

	EnemyState enemyState;						//エネミーの状態

	std::vector<VECTOR>::iterator itr;
	std::vector<VECTOR> pointList;

	float cakeCount;		//エネミーのケーキの反応カウント
	bool cakeFindFlag;		//エネミーがケーキを見つけたかどうか
	bool cakeEatFlag;		//エネミーがケーキに近づいて食べているかどうか
	bool cakeHalfFlag;		//ケーキが半分になっているかどうか

	VECTOR a;

	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string PLAYER_FIND_PATH;	//プレイヤーを見つけた画像のパス
	static const std::string MARK_PATH;			//ビックリマーク画像のパス
	static const std::string CAKE_PATH;			//ケーキ画像のパス
	static const std::string CAKE_HALF_PATH;	//ケーキが半分の画像のパス


};