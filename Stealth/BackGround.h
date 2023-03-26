#pragma once

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

    void Update();              //更新処理
    void Draw();                //描画処理

private:
    BackGround(const BackGround&);      //コピーコンストラクタ

    void Initialize();          //初期化処理
    void Finalize();            //終了処理

    int backGroundHandle;       //背景動画格納用

    //定数
    const string VIDEO_FOLDER_PATH;	        //Videoフォルダまでのパス
    const string BACKGROUND_VIDEO_PATH;	    //背景動画のパス
    const int    PLAY_POSITION;             //動画再生位置

};