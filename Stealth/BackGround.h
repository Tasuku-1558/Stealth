#pragma once

#include "DxLib.h"
#include "ObjectBase.h"

/// <summary>
/// ステージクラス
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

    //静的定数
    static const VECTOR SIZE;

};