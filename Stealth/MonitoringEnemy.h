#pragma once

#include <vector>
#include <string>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"

class Player;
class Bullet;
class HitChecker;

/// <summary>
/// 監視エネミークラス
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(const VECTOR& pos, VECTOR changeDir, VECTOR currentDir);
	virtual ~MonitoringEnemy();

	void Initialize();									//初期化処理
	void Activate();									//活性化処理
	void Update(float deltaTime, Player* player, HitChecker* hitChecker);	//更新処理
	void Draw();										//描画処理

	const bool Spotted() { return playerSpotted; }			//プレイヤーを見つけたかどうかを返す

private:
	MonitoringEnemy(const MonitoringEnemy&);	//コピーコンストラクタ

	void VisualAnglePlayer(Player* player);		//エネミーの視野にプレイヤーが入った場合
	void DirMove(float deltaTime);				//エネミーの向きの処理
	void Reaction();							//エネミーのプレイヤーの反応
	void ReactionDraw();						//リアクション画像の描画処理
	void Finalize();							//終了処理

	std::string InputPath(std::string folderPath, //画像のパスを入力
						  std::string imagePath);

	float dirCount;			//向き変更カウント
	VECTOR anotherDir;		//別の向き
	VECTOR initialDir;		//初期の向き

	//静的定数
	static const std::string IMAGE_FOLDER_PATH;	//imageフォルダまでのパス
	static const std::string PLAYER_FIND_PATH;	//プレイヤーを見つけた画像のパス
	static const std::string MARK_PATH;			//ビックリマーク画像のパス
};