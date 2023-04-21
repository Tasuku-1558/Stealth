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

	int  keyReleaseCount;         //連続キー入力がないカウント
	char currentKeyState[256];    //現在のキー押下状態
	char prevKeyState[256];       //前フレームのキー押下状態

	//定数
	const int KEY_NUMBER;				//キーの数
	const int INITIAL_RELEASE_COUNT;	//初期の連続キー入力がないカウント
};