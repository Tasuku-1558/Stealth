#include "CakeManager.h"
#include "CakeBullet.h"
#include "EffectManager.h"


CakeManager::CakeManager()
{
	CakePop();
}

CakeManager::~CakeManager()
{

}

void CakeManager::Update(float deltaTime, Player* player)
{
	for (auto cakeBulletPtr : cakeBullet)
	{
		cakeBulletPtr->Update(deltaTime, player);
	}
}

void CakeManager::Draw()
{
	for (auto cakeBulletPtr : cakeBullet)
	{
		cakeBulletPtr->Draw();
	}
}

void CakeManager::EntryCake(CakeBullet* newCakeBullet)
{
	cakeBullet.emplace_back(newCakeBullet);
}

void CakeManager::DeleteCake(CakeBullet* deleteCakeBullet)
{
	//ケーキバレットオブジェクトから検索して削除
	auto iter = std::find(cakeBullet.begin(), cakeBullet.end(), deleteCakeBullet);

	if (iter != cakeBullet.end())
	{
		//ケーキバレットオブジェクトを最後尾に移動してデータを消す
		std::iter_swap(iter, cakeBullet.end() - 1);
		cakeBullet.pop_back();

		return;
	}
}

void CakeManager::CakePop()
{
	CakeBullet* newCakeBullet = new CakeBullet(/*{ 0.0f,30.0f,0.0f }*/effectManager);
	EntryCake(newCakeBullet);
}