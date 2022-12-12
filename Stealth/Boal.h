#pragma once

#include "ObjectBase.h"

/// <summary>
/// ボールクラス
/// </summary>
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