#include "InputManager.h"


namespace Input
{
	/// <summary>
	/// パスの入力
	/// </summary>
	/// <param name="folderPath">フォルダまでのパス</param>
	/// <param name="path">パス</param>
	/// <returns>パスを返す</returns>
	string InputPath(string folderPath, string path)
	{
		return string(folderPath + path);
	}
}