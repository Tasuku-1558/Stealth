#pragma once


/// <summary>
/// �f���^�^�C���N���X
/// �V���O���g��
/// </summary>
class DeltaTime final
{
public:

	static DeltaTime& GetInstance();		//�A�h���X��Ԃ�

	void Initialize();						//����������
	void DeltaTimeCount();					//60Fps�v��

	//const float GetDeltaTime() { return deltaTime; }	//�f���^�^�C����Ԃ�

private:

	DeltaTime();
	DeltaTime(const DeltaTime&);			//�R�s�[�R���X�g���N�^
	virtual ~DeltaTime();

	//float deltaTime;		//�O�t���[���ƌ��݂̃t���[���̍���
	//float waitFrameTime;	//�ҋ@�t���[������(60fps)
	//LONGLONG nowTime;		//���݂̃t���[��
	//LONGLONG prevTime;		//�̂̃t���[��
};