#include "InputManager.h"


namespace Input
{
	/// <summary>
	/// �f�[�^�̃p�X�̓���
	/// </summary>
	/// <param name="folderPath">�t�H���_�܂ł̃p�X</param>
	/// <param name="dataPath">�f�[�^�܂ł̃p�X</param>
	/// <returns>�p�X��Ԃ�</returns>
	string InputPath(string folderPath, string dataPath)
	{
		return string(folderPath + dataPath);
	}
}