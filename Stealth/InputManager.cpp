#include "InputManager.h"


namespace Input
{
	/// <summary>
	/// �p�X�̓���
	/// </summary>
	/// <param name="folderPath">�t�H���_�܂ł̃p�X</param>
	/// <param name="path">�p�X</param>
	/// <returns>�p�X��Ԃ�</returns>
	string InputPath(string folderPath, string path)
	{
		return string(folderPath + path);
	}
}