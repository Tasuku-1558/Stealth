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

	void EntryCake(CakeBullet* newCakeBullet);		//�P�[�L��o�^
	void DeleteCake(CakeBullet* deleteCakeBullet);	//�P�[�L���폜
	void CakePop();						//�P�[�L�̏o��

	EffectManager* effectManager;
	std::vector<CakeBullet*> cakeBullet;


};