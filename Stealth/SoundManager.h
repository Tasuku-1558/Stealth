#pragma once

#include <string>

/// <summary>
/// �T�E���h�Ǘ��N���X
/// �V���O���g��
/// </summary>
class SoundManager final
{
public:
	SoundManager();
	virtual ~SoundManager();

	void Initialize();

	static SoundManager& GetInstance(); //�A�h���X��Ԃ�

	void PlayBgm(); //�w���BGM���Đ��J�n
	void StopBgm();
	void DeleteBgm();

private:
	SoundManager(const SoundManager&);		//�R�s�[�R���X�g���N�^

	std::string InputPath(std::string folderPath,	//�摜�̃p�X�����
						  std::string path);

	int bgmData[2];

	//�ÓI�萔
	static const std::string SOUND_FOLDER_PATH;		//sound�t�H���_�܂ł̃p�X
	static const std::string GAME_BGM_PATH;			//�Q�[����ʂ�BGM���̃p�X

};