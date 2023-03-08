#pragma once

/// <summary>
/// キー入力管理クラス
/// シングルトン
/// </summary>
class KeyManager final
{
public:

	static KeyManager& GetInstance();		//アドレスを返す

	void Update();							//更新処理

	bool CheckPressed(int keyCode) const;   //キーが押されているか

private:
	KeyManager();
	KeyManager(const KeyManager&);			//コピーコンストラクタ
	virtual ~KeyManager();


	char currentKeyState[256];    //現在のキー押下状態
	char prevKeyState[256];       //前フレームのキー押下状態
	int  keyReleaseCount;         //連続キー入力がないカウント
};