#pragma once

#include <stdio.h>
#include <memory.h>
#include <list>

using namespace std;


// �m�[�h�̒�`
struct node
{
	short cost;		// ���Y�m�[�h�܂ł̃R�X�g
	short score;	// ���Y�m�[�h�]���l
	char state;		// �m�[�h���
	char direction;	// �e�m�[�h�̕���

};

struct position
{
	int x;
	int y;

	// ������Z�q�̃I�[�o�[���[�h
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

// �n�`�̎��
enum CHIPTYPE { PLANE, WALL, } chipType;

// �m�[�h��Ԓ萔
enum STATE { UNCHECKED, IN_OPEN_LIST, IN_CLOSE_LIST, } state;

#define DIR_MAX 8				// �΂߈ړ��������Ȃ��ꍇ��4���w�肷��
#define MAP_WIDTHMAX	10		// �}�b�v��
#define MAP_HEIGHTMAX	10		// �}�b�v����
#define COORDINATE_ELEMENT_MAX 2	// x, y�̂Q��

#define X_ELM 0					// �e�q�m�[�h��x����
#define Y_ELM 1					// �e�q�m�[�h��y����

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

// �n�`�R�X�g(�n�`�ɂ��R�X�g�����Ȃ��ꍇ�͕ǈȊO�����ׂ�1�ɂ���)
short chip_cost[] = { 1, 3, 5, 255 };

// �}�b�v
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
	// �m�[�h�p�������̊m��
	static node mapNode[MAP_HEIGHTMAX][MAP_WIDTHMAX];

	// �m�[�h�p���[�N�ϐ�
	position current{};

	int tmpX, tmpY;					// �אڍ��W
	int deltaX, deltaY;				// x,y����
	short cost, score, heuristic;	// �]���l�v�Z�p
	list<position> result;

	// node�f�[�^�̏�����
	memset(mapNode, 0, sizeof(mapNode));

	// �I�[�v�����X�g�̍쐬
	list<position> open_list = { start };

	// �Ƃ肠�����X�^�[�g�n�_���I�[�v�����X�g�ɒǉ������t���O�𗧂Ă�
	mapNode[start.y][start.x].state = IN_OPEN_LIST;

	// �I�[�v�����X�g����ɂȂ�܂ŌJ��Ԃ�
	while (!open_list.empty())
	{
		if (open_list.front() == goal)
		{
			// �S�[���ɓ��B
			result.push_front(goal);

			// �S�[������e�m�[�h�֏��ɒH��Ȃ��烋�[�g���i�[����
			// ���]�������ȗ�
			for (current = open_list.front(); current != start; result.push_front(current))
			{
				node& current_node = mapNode[current.y][current.x];
				current.x -= directionDelta[current_node.direction][X_ELM];
				current.y -= directionDelta[current_node.direction][Y_ELM];
			}

			break;
		}

		// �I�[�v�����X�g�̐擪�v�f���擾
		current = open_list.front();
		node& current_node = mapNode[current.y][current.x];

		// �����B�Ȃ̂Ŏ��͂̃Z��������(i���e������\�����Ƃɒ��ӂ���)
		for (int i = 0; i < DIR_MAX; i++)
		{
			// �׃Z���ʒu���v�Z
			tmpX = current.x + directionDelta[i][X_ELM];
			tmpY = current.y + directionDelta[i][Y_ELM];

			// �׃Z�����}�b�v�O��������`�F�b�N���Ȃ�
			if (tmpX < 0 || tmpX == MAP_WIDTHMAX)
			{
				continue;
			}
			if (tmpY < 0 || tmpY == MAP_HEIGHTMAX)
			{
				continue;
			}

			// �ǂ�������`�F�b�N���Ȃ�
			char chip_type = map[tmpY][tmpX];
			if (chip_type == WALL)
			{
				continue;
			}

			node& next_node = mapNode[tmpY][tmpX];

			// �I�[�v�����X�g���N���[�Y���X�g���肾������`�F�b�N���Ȃ�
			if (next_node.state != UNCHECKED)
			{
				continue;
			}

			// �׃Z���̃R�X�g�A�X�R�A�A�q���[���X�e�B�b�N�̌v�Z
			cost = current_node.cost + chip_cost[chip_type];
			deltaX = tmpX > goal.x ? tmpX - goal.x : goal.x - tmpX;
			deltaY = tmpY > goal.y ? tmpY - goal.y : goal.y - tmpY;
#if DIR_MAX == 8
			// 8�����ړ��̏ꍇ�̃q���[���X�e�B�b�N
			heuristic = (short)(deltaX > deltaY ? deltaX : deltaY);
#else
			// 4�����ړ��̏ꍇ�̃q���[���X�e�B�b�N
			heuristic = (short)(deltax + deltay);
#endif
			score = cost + heuristic;

			// �R�X�g�A�X�R�A��׃Z���m�[�h�ɋL��
			next_node.cost = cost;
			next_node.score = score;
			next_node.direction = (char)i;			// �e�Z���̕���

			// �׃Z���m�[�h���I�[�v�����X�g�ɒǉ�����
			next_node.state = IN_OPEN_LIST;
			list<position>::iterator iter;

			// �I�[�v�����X�g���̃m�[�h���X�R�A�̏����ɂȂ�悤�ɐV�m�[�h��}������
			for (iter = open_list.begin(); iter != open_list.end(); ++iter)
			{
				if (score <= mapNode[iter->y][iter->x].score)
				{
					open_list.insert(iter, { tmpX, tmpY });
					break;
				}
			}

			// �C�e���[�^�����X�g�̏I�[�́u���v�ɓ��B�����Ȃ�΁A�}���ł��Ă��Ȃ�
			// �i���ߋ��ň��̃X�R�A�j�Ȃ̂ŁA�I�[�v�����X�g�̖����ɐV�m�[�h��}������
			if (iter == open_list.end())
			{
				open_list.push_back({ tmpX, tmpY });
			}
		}

		// ���݈ʒu���N���[�Y����
		current_node.state = IN_CLOSE_LIST;
		open_list.remove(current);
	}

	// �R���e�i��Ԃ�
	return result;
}