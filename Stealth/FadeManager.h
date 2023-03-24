#pragma once

/// <summary>
/// 画面効果クラス
/// </summary>
class FadeManager final
{
public:
	FadeManager();
	virtual ~FadeManager();

	void FadeMove();					//画面効果処理
	void Draw();						//描画処理

private:
	FadeManager(const FadeManager&);	//コピーコンストラクタ

	int fade;
	int fadeInc;

	//定数
	const int BLACK;			//フェードのカラー
	const int MAX_FADE;
};