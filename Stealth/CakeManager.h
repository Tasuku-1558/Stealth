#pragma once

#include <vector>
#include "DxLib.h"

class Cake;

using namespace std;

class CakeManager final
{
public:

	CakeManager(vector<Cake*>* const inCakePosition);
	virtual ~CakeManager();

private:

	vector<Cake*>* const cakePosition;

};