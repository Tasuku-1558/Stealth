#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "PreCompiledHeader.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "SoundManager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);			//ログファイルを出力しない
	ChangeWindowMode(IS_WINDOW_MODE);				//ウィンドウモードにするか
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);	//画面モードのセット
	SetUseDirect3DVersion(DX_DIRECT3D_11);			//DirectX11を使用するようにする
	
	//Dxlibの初期化処理
	if (DxLib_Init() == -1)		
	{
		return -1;			//エラーが起きたら直ちに終了
	}

	//Effekseerの初期化処理
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//描画先画面を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	
	//フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//Zバッファを有効にする
	SetUseZBuffer3D(TRUE);

	//Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	//// シャドウマップハンドルの作成
	//int shadowMapHandle = MakeShadowMap(SHADOWMAP_SIZE_X, SHADOWMAP_SIZE_Y);

	//// シャドウマップが想定するライトの方向をセット
	//SetShadowMapLightDirection(shadowMapHandle, LIGHT_DIRECTION);

	//// シャドウマップに描画する範囲を設定
	//SetShadowMapDrawArea(shadowMapHandle, SHADOWMAP_MINPOSITION, SHADOUMAP_MAXPOSITION);
	
	//フォントの読み込み
	LPCSTR fontPath = "data/font/Oranienbaum.ttf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {}
	else { MessageBox(NULL, "フォント読込失敗", "", MB_OK); }

	//時間計測
	LONGLONG nowTime;
	LONGLONG prevTime = nowTime = GetNowHiPerformanceCount();

	//待機フレーム時間(60fps)
	float waitFrameTime = 16667.0f;
	
	//モデル管理クラスの生成
	ModelManager::GetInstance();

	//サウンド管理クラスの生成
	SoundManager::GetInstance();

	SceneManager* sceneManager = new SceneManager();

	sceneManager->Initialize();
	
	//エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//前フレームと現在のフレームの差分
		float deltaTime;

		//現在のフレームを更新
		nowTime = GetNowHiPerformanceCount();

		deltaTime = (nowTime - prevTime) / 1000000.0f;

		// DxlibのカメラとEffekseerのカメラを同期
		Effekseer_Sync3DSetting();

		KeyManager::GetInstance().Update();

		SoundManager::GetInstance().SeUpdate();

		sceneManager->Update(deltaTime);

		//画面を初期化する
		ClearDrawScreen();

		//// シャドウマップへの描画の準備
		//ShadowMap_DrawSetup(shadowMapHandle);

		sceneManager->Draw();

		//デバック用　デルタタイム計測
		DrawFormatString(0, 500, GetColor(255, 255, 255),"%f", deltaTime, TRUE);

		//// シャドウマップへの描画を終了
		//ShadowMap_DrawEnd();


		//// 描画に使用するシャドウマップを設定
		//SetUseShadowMap(0, shadowMapHandle);

		//sceneManager->Draw();

		//// 描画に使用するシャドウマップの設定を解除
		//SetUseShadowMap(0, -1);

		//裏画面の内容を表画面に反映させる
		ScreenFlip();

		//次のシーンがENDなら
		if (sceneManager->GetNextScene() == SceneManager::END)
		{
			break;
		}

		//60fps制御用ループ
		while (GetNowHiPerformanceCount() - nowTime < waitFrameTime);

		//現在のフレームを保存
		prevTime = nowTime;
	}

	//フォントのアンロード
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	//DeleteShadowMap(shadowMapHandle);	// シャドウマップの削除

	SafeDelete(sceneManager);	//シーンマネージャーの解放

	Effkseer_End();				//Effekseerの終了処理

	DxLib_End();				//Dxlibの終了処理

	return 0;					//ソフトの終了 
}