#pragma once

#include "ObjectBase.h"

/// <summary>
/// StageBase�N���X
/// </summary>
class StageBase : public ObjectBase
{
public:
	StageBase();
	virtual ~StageBase();

protected:

	int x;
	int y;
	int mapGraph;
	int pDotX;
	int pDotY;
	int mapFlameX;
	int mapFlameY;
	double exRate;
	int miniMapWidth;
	int miniMapHeight;
	int dotSize;
};