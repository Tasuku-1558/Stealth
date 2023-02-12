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
	MonitoringEnemy(const VECTOR& pos, VECTOR changeDir);
	virtual ~MonitoringEnemy();

	void Initialize();									//初期化処理
	void Activate();									//活性化処理
	void Update(float deltaTime, Player* player);		//更新処理
	void Draw();										//描画処理

	void VisualAngleWall(VECTOR wallPos);					//エネミーの視野に壁が入った場合

	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す

private:
	MonitoringEnemy(const MonitoringEnemy&);	//コピーコンストラクタ

	void VisualAnglePlayer(Player* player);		//エネミーの視野にプレイヤーが入った場合
	void DirMove(float deltaTime);				//エネミーの向きの処理
	void Reaction();							//エネミーのオブジェクトごとの反応
	void ReactionDraw();						//リアクション画像の描画処理
	void Finalize();							//終了処理

	std::string InputPath(std::string folderPath, //画像のパスを入力
		std::string imagePath);

	float count;
	VECTOR anotherDir;

	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string PLAYER_FIND_PATH;	//プレイヤーを見つけた画像のパス
	static const std::string MARK_PATH;			//ビックリマーク画像のパス


};