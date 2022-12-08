#pragma once

#include "ObjectBase.h"

class Field final : public ObjectBase
{
public:
	 Field();
	~Field();

	void Initialize();
	void Finalize();
	void Activate();

	void Update();
	void Draw();

private:

	static const VECTOR POSITION;
};