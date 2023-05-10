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

    void Update();   //更新処理
    void Draw();     //描画処理

private:
    BackGround(const BackGround&);      //コピーコンストラクタ

    void Initialize();          //初期化処理

    int backGroundHandle;       //背景動画格納用

    //定数
    const int    PLAY_POSITION;             //動画再生位置
    const int    BACKGROUND_MOVIE_POS_X;    //背景動画のX座標
    const int    BACKGROUND_MOVIE_POS_Y;    //背景動画のY座標
    const string VIDEO_FOLDER_PATH;	        //Videoフォルダまでのパス
    const string BACKGROUND_VIDEO_PATH;	    //背景動画のパス

};