//-----------------------------------------------------------------------------
// ���C������
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Common.h"
#include "ModelManager.h"
#include "PlayScene.h"

//�f�o�b�N�p
#define LINE_AREA_SIZE		10000.0f
#define LINE_NUM			50

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

	PlayScene* playScene = new PlayScene();

	playScene->Initialize();
	playScene->Activate();
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���[�����Ԃ��Z�o
		float deltaTime = 0.0f;
		nowTime = GetNowCount();

		deltaTime = (nowTime - prevTime) / 1000.0f;

		prevTime = nowTime;

		playScene->Update(deltaTime);

		// ��ʂ�����������
		ClearDrawScreen();

		playScene->Draw();

		//�f�o�b�N�p
		{
			int i;
			VECTOR Pos1;
			VECTOR Pos2;

			SetUseZBufferFlag(TRUE);

			Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
			for (i = 0; i <= LINE_NUM; i++)
			{
				DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
				Pos1.x += LINE_AREA_SIZE / LINE_NUM;
				Pos2.x += LINE_AREA_SIZE / LINE_NUM;
			}

			Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
			for (i = 0; i < LINE_NUM; i++)
			{
				DrawLine3D(Pos1, Pos2, GetColor(255, 255, 255));
				Pos1.z += LINE_AREA_SIZE / LINE_NUM;
				Pos2.z += LINE_AREA_SIZE / LINE_NUM;
			}

			SetUseZBufferFlag(FALSE);
		}

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();
	}

	//�t�H���g�̃A�����[�h
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	SafeDelete(playScene);

	DxLib_End();			// DX���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}