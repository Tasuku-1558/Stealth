#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "PreCompiledHeader.h"
#include "SceneBase.h"
#include "ModelManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

#include "TitleScene.h"


//メインプログラム
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(IS_WINDOW_MODE);						//ウィンドウモードにするか
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT);	//画面モードのセット
	SetUseDirect3DVersion(DX_DIRECT3D_11);					//DirectX11を使用するようにする
	SetOutApplicationLogValidFlag(FALSE);					//ログファイルを出力しない

	//Dxlibの初期化処理
	if (DxLib_Init() == -1)		
	{
		return -1;			//エラーが起きたら直ちに終了
	}

	//Effekseerの初期化処理
	//引数は画面に表示する最大パーティクル数を設定
	if (Effekseer_Init(MAX_PARTICLE_NUMBER) == -1)
	{
		DxLib_End();
		return -1;
	}

	//描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	
	//フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//Dxlibがデバイスロストした時のコールバックを設定する
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//Zバッファを有効にする
	SetUseZBuffer3D(TRUE);

	//Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);
	
	//フォントの読み込み
	LPCSTR fontPath = "Data/Font/Oranienbaum.ttf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {}
	else { MessageBox(NULL, "フォントの読込失敗", "", MB_OK); }

	//時間計測
	LONGLONG nowTime;
	LONGLONG prevTime = nowTime = GetNowHiPerformanceCount();

	//待機フレーム時間(60fps)
	float waitFrameTime = 16667.0f;

	//メインループ用フラグ変数
	bool loop = true;

	//モデル管理クラスの生成
	ModelManager::GetInstance();

	//サウンド管理クラスの生成
	SoundManager::GetInstance();

	//今のシーン
	SceneType nowSceneType;

	//ひとつ前のシーン
	SceneType prevSceneType = nowSceneType = SceneType::TITLE;

	//シーンを生成
	SceneBase* sceneBase = new TitleScene();
	
	//メインループ
	while (loop)
	{
		//前フレームと現在のフレームの差分
		float deltaTime;

		//現在のフレームを更新
		nowTime = GetNowHiPerformanceCount();

		//差分を100万分の1にして保存する(マイクロ秒換算)
		deltaTime = (nowTime - prevTime) / 1000000.0f;

		//マウスカーソルを表示しない
		SetMouseDispFlag(FALSE);

		//DxlibのカメラとEffekseerのカメラを同期
		Effekseer_Sync3DSetting();

		KeyManager::GetInstance().Update();

		SoundManager::GetInstance().SeUpdate();

		//各シーンの更新処理
		nowSceneType = sceneBase->Update(deltaTime);

		//画面を初期化する
		ClearDrawScreen();

		//各シーンの描画処理
		sceneBase->Draw();

		//デバック用　デルタタイム計測
		DrawFormatString(0, 500, GetColor(255, 255, 255), "%f", deltaTime, TRUE);
		DrawFormatString(0, 550, GetColor(255, 255, 255), "%d", sceneBase->Get(), TRUE);


		//裏画面の内容を表画面に反映させる
		ScreenFlip();

		//次のシーンがENDならメインループを抜ける
		if (nowSceneType == SceneType::END || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			loop = false;
			break;
		}

		//今のシーンが前のシーンと違うなら
		if (nowSceneType != prevSceneType)
		{
			delete sceneBase;									//シーンの解放
			sceneBase = sceneBase->CreateScene(nowSceneType);	//新しいシーンの生成
		}

		//直前のシーンを記録
		prevSceneType = nowSceneType;

		//60fps制御用ループ
		while (GetNowHiPerformanceCount() - nowTime < waitFrameTime);

		//現在のフレームを保存
		prevTime = nowTime;
	}

	//フォントの削除
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	delete sceneBase;		//シーンの解放

	Effkseer_End();			//Effekseerの終了処理

	DxLib_End();			//Dxlibの終了処理

	return 0;				//ソフトの終了 
}