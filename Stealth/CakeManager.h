#pragma once

#include <vector>
#include "DxLib.h"

class EffectManager;
class Player;
class CakeBullet;

using namespace std;

class CakeManager final
{
public:

	CakeManager();
	virtual ~CakeManager();

	void Update(float deltaTime, Player* player);
	void Draw();

private:

	void EntryCake(CakeBullet* newCakeBullet);		//ケーキを登録
	void DeleteCake(CakeBullet* deleteCakeBullet);	//ケーキを削除
	void CakePop();						//ケーキの出現

	EffectManager* effectManager;
	std::vector<CakeBullet*> cakeBullet;


};