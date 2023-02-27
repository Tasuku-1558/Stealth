#pragma once

#include "DxLib.h"
#include <string>

using namespace std;

/// <summary>
/// 背景動画クラス
/// </summary>
class BackGround final
{
public:
    BackGround();
    virtual ~BackGround();

    void Initialize();          //初期化処理
    void Finalize();            //終了処理
    void Activate();            //活性化処理
    void Update();              //更新処理
    void Draw();                //描画処理

private:

    int backGroundHandle;       //背景動画格納用

    //定数
    const string VIDEO_FOLDER_PATH;	        //videoフォルダまでのパス
    const string BACK_GROUND_VIDEO_PATH;	//背景動画のパス

};