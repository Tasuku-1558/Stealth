//-----------------------------------------------------------------------------
// ���C������
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "SceneManager.h"

//-----------------------------------------------------------------------------
// ���C���֐�
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);			// ���O�t�@�C�����o�͂��Ȃ�
	ChangeWindowMode(IS_WINDOW_MODE);				// �E�B���h�E���[�h�ɂ��邩
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);	// ��ʃ��[�h�̃Z�b�g

	// DX���C�u��������������
	if (DxLib_Init() == -1)		
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �t�H���g�ύX
	LPCSTR fontPath = "data/font/Oranienbaum.ttf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {}
	else { MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK); }

	// ���Ԍv��
	int nowTime;
	int prevTime = nowTime = GetNowCount();
	
	ModelManager::GetInstance();	//���f���Ǘ��N���X�̐���

	SceneManager* sceneManager = new SceneManager();

	sceneManager->Initialize();
	
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���[�����Ԃ��Z�o
		float deltaTime = 0.0f;
		nowTime = GetNowCount();

		deltaTime = (nowTime - prevTime) / 1000.0f;

		prevTime = nowTime;

		sceneManager->Update(deltaTime);

		// ��ʂ�����������
		ClearDrawScreen();

		sceneManager->Draw();

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// ���̃V�[����END�Ȃ�
		if (sceneManager->GetNextScene() == SceneManager::END)
		{
			break;
		}
	}

	//�t�H���g�̃A�����[�h
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	SafeDelete(sceneManager);

	DxLib_End();			// DX���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}