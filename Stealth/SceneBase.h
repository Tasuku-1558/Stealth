#pragma once

/// <summary>
/// シーンベースクラス
/// </summary>
class SceneBase
{
public:
	SceneBase() {/*処理なし*/ }			//コンストラクタ
	virtual ~SceneBase() {/*処理なし*/}	//デストラクタ

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Activate() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:


private:
	SceneBase(const SceneBase&);		//コピーコンストラクタ
};