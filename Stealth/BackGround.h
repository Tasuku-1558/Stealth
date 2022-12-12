#pragma once

#include "DxLib.h"
#include "ObjectBase.h"

/// <summary>
/// �X�e�[�W�N���X
/// </summary>
class BackGround final : public ObjectBase
{
public:
     BackGround();
    ~BackGround();

    void Initialize();
    void Finalize();
    void Activate();
    void Update();
    void Draw();


private:

    //�ÓI�萔
    static const VECTOR SIZE;

};