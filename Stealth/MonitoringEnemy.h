#pragma once

#include <vector>

#include "DxLib.h"
#include "EnemyBase.h"
#include "Math3D.h"


/// <summary>
/// �Ď��G�l�~�[�N���X
/// </summary>
class MonitoringEnemy final : public EnemyBase
{
public:
	MonitoringEnemy(std::vector<VECTOR>& id);
	virtual ~MonitoringEnemy();

	void Initialize();									//����������
	void Activate();									//����������
	void Update(float deltaTime);						//�X�V����
	void Draw();										//�`�揈��


private:



};