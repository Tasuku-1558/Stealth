#pragma once

#include "ObjectBase.h"

class Boal final : public ObjectBase
{
public:
	 Boal();
	~Boal();

	void Initialize();
	void Finalize();
	void Activate();

	void Update();
	void Draw();

private:

	static const VECTOR POSITION;
};