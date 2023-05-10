#include "InputManager.h"


namespace Input
{
	/// <summary>
	/// データのパスの入力
	/// </summary>
	/// <param name="folderPath">フォルダまでのパス</param>
	/// <param name="dataPath">データまでのパス</param>
	/// <returns>パスを返す</returns>
	string InputPath(string folderPath, string dataPath)
	{
		return string(folderPath + dataPath);
	}
}