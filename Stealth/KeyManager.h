#pragma once

/// <summary>
/// �L�[���͊Ǘ��N���X
/// �V���O���g��
/// </summary>
class KeyManager final
{
public:

	static KeyManager& GetInstance();		//�A�h���X��Ԃ�

	void Update();							//�X�V����

	bool CheckPressed(int keyCode) const;   //�L�[��������Ă��邩

private:
	KeyManager();
	KeyManager(const KeyManager&);			//�R�s�[�R���X�g���N�^
	virtual ~KeyManager();


	char currentKeyState[256];    //���݂̃L�[�������
	char prevKeyState[256];       //�O�t���[���̃L�[�������
	int  keyReleaseCount;         //�A���L�[���͂��Ȃ��J�E���g
};