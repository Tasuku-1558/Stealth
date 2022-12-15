#pragma once

#include <stdio.h>
#include <memory.h>
#include <list>

using namespace std;


// ノードの定義
struct node
{
	short cost;		// 当該ノードまでのコスト
	short score;	// 当該ノード評価値
	char state;		// ノード状態
	char direction;	// 親ノードの方向

};

struct position
{
	int x;
	int y;

	// 代入演算子のオーバーロード
	struct position& operator=(const struct position& v)
	{
		this->x = v.x;
		this->y = v.y;

		return *this;
	}

};

bool operator==(const position& o1, const position& o2)
{
	return o1.x == o2.x && o1.y == o2.y;
}

bool operator!=(const position& o1, const position& o2)
{
	return o1.x != o2.x || o1.y != o2.y;
}

// 地形の種類
enum CHIPTYPE { PLANE, WALL, } chipType;

// ノード状態定数
enum STATE { UNCHECKED, IN_OPEN_LIST, IN_CLOSE_LIST, } state;

#define DIR_MAX 8				// 斜め移動を許可しない場合は4を指定する
#define MAP_WIDTHMAX	10		// マップ幅
#define MAP_HEIGHTMAX	10		// マップ高さ
#define COORDINATE_ELEMENT_MAX 2	// x, yの２つ

#define X_ELM 0					// 親子ノードのx成分
#define Y_ELM 1					// 親子ノードのy成分

int directionDelta[DIR_MAX][2] =
{
#if DIR_MAX == 8
	{ -1,-1 },{  0,-1 },{ +1,-1 },
	{ -1, 0 },{ +1, 0 },
	{ -1,+1 },{  0,+1 },{ +1,+1 },
#else
	{  0,-1 },{ -1, 0 },{ +1, 0 },{ 0, +1 },
#endif
};

// 地形コスト(地形によるコスト差がない場合は壁以外をすべて1にする)
short chip_cost[] = { 1, 3, 5, 255 };

// マップ
char map[MAP_HEIGHTMAX][MAP_WIDTHMAX] =
{
	{ 3,3,1,0,2,0,0,0,1,0, },
	{ 0,0,0,2,0,1,2,0,0,0, },
	{ 0,0,2,3,3,3,3,3,2,1, },
	{ 0,2,0,1,0,0,0,3,0,0, },
	{ 0,0,0,2,0,0,2,3,1,2, },
	{ 0,3,3,0,0,2,0,3,1,0, },
	{ 0,3,3,0,0,0,1,1,0,0, },
	{ 0,3,3,3,3,0,2,0,3,2, },
	{ 0,0,2,0,0,0,0,3,3,0, },
	{ 0,0,0,0,2,0,0,2,0,0, },
};

list<position> PathSearch(position start, position goal)
{
	// ノード用メモリの確保
	static node mapNode[MAP_HEIGHTMAX][MAP_WIDTHMAX];

	// ノード用ワーク変数
	position current{};

	int tmpX, tmpY;					// 隣接座標
	int deltaX, deltaY;				// x,y差分
	short cost, score, heuristic;	// 評価値計算用
	list<position> result;

	// nodeデータの初期化
	memset(mapNode, 0, sizeof(mapNode));

	// オープンリストの作成
	list<position> open_list = { start };

	// とりあえずスタート地点をオープンリストに追加したフラグを立てる
	mapNode[start.y][start.x].state = IN_OPEN_LIST;

	// オープンリストが空になるまで繰り返す
	while (!open_list.empty())
	{
		if (open_list.front() == goal)
		{
			// ゴールに到達
			result.push_front(goal);

			// ゴールから親ノードへ順に辿りながらルートを格納する
			// 反転処理を省略
			for (current = open_list.front(); current != start; result.push_front(current))
			{
				node& current_node = mapNode[current.y][current.x];
				current.x -= directionDelta[current_node.direction][X_ELM];
				current.y -= directionDelta[current_node.direction][Y_ELM];
			}

			break;
		}

		// オープンリストの先頭要素を取得
		current = open_list.front();
		node& current_node = mapNode[current.y][current.x];

		// 未到達なので周囲のセルを検査(iが各方向を表すことに注意する)
		for (int i = 0; i < DIR_MAX; i++)
		{
			// 隣セル位置を計算
			tmpX = current.x + directionDelta[i][X_ELM];
			tmpY = current.y + directionDelta[i][Y_ELM];

			// 隣セルがマップ外だったらチェックしない
			if (tmpX < 0 || tmpX == MAP_WIDTHMAX)
			{
				continue;
			}
			if (tmpY < 0 || tmpY == MAP_HEIGHTMAX)
			{
				continue;
			}

			// 壁だったらチェックしない
			char chip_type = map[tmpY][tmpX];
			if (chip_type == WALL)
			{
				continue;
			}

			node& next_node = mapNode[tmpY][tmpX];

			// オープンリストかクローズリスト入りだったらチェックしない
			if (next_node.state != UNCHECKED)
			{
				continue;
			}

			// 隣セルのコスト、スコア、ヒューリスティックの計算
			cost = current_node.cost + chip_cost[chip_type];
			deltaX = tmpX > goal.x ? tmpX - goal.x : goal.x - tmpX;
			deltaY = tmpY > goal.y ? tmpY - goal.y : goal.y - tmpY;
#if DIR_MAX == 8
			// 8方向移動の場合のヒューリスティック
			heuristic = (short)(deltaX > deltaY ? deltaX : deltaY);
#else
			// 4方向移動の場合のヒューリスティック
			heuristic = (short)(deltax + deltay);
#endif
			score = cost + heuristic;

			// コスト、スコアを隣セルノードに記入
			next_node.cost = cost;
			next_node.score = score;
			next_node.direction = (char)i;			// 親セルの方向

			// 隣セルノードをオープンリストに追加する
			next_node.state = IN_OPEN_LIST;
			list<position>::iterator iter;

			// オープンリスト内のノードがスコアの昇順になるように新ノードを挿入する
			for (iter = open_list.begin(); iter != open_list.end(); ++iter)
			{
				if (score <= mapNode[iter->y][iter->x].score)
				{
					open_list.insert(iter, { tmpX, tmpY });
					break;
				}
			}

			// イテレータがリストの終端の「次」に到達したならば、挿入できていない
			// （＝過去最悪のスコア）なので、オープンリストの末尾に新ノードを挿入する
			if (iter == open_list.end())
			{
				open_list.push_back({ tmpX, tmpY });
			}
		}

		// 現在位置をクローズする
		current_node.state = IN_CLOSE_LIST;
		open_list.remove(current);
	}

	// コンテナを返す
	return result;
}