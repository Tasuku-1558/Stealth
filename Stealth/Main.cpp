#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "PreCompiledHeader.h"
#include "SceneBase.h"
#include "ModelManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

#include "TitleScene.h"


//���C���v���O����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(IS_WINDOW_MODE);						//�E�B���h�E���[�h�ɂ��邩
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT);	//��ʃ��[�h�̃Z�b�g
	SetUseDirect3DVersion(DX_DIRECT3D_11);					//DirectX11���g�p����悤�ɂ���
	SetOutApplicationLogValidFlag(FALSE);					//���O�t�@�C�����o�͂��Ȃ�

	//Dxlib�̏���������
	if (DxLib_Init() == -1)		
	{
		return -1;			//�G���[���N�����璼���ɏI��
	}

	//Effekseer�̏���������
	//�����͉�ʂɕ\������ő�p�[�e�B�N������ݒ�
	if (Effekseer_Init(MAX_PARTICLE_NUMBER) == -1)
	{
		DxLib_End();
		return -1;
	}

	//�`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	
	//�t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//Dxlib���f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	//Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);
	
	//�t�H���g�̓ǂݍ���
	LPCSTR fontPath = "Data/Font/Oranienbaum.ttf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {}
	else { MessageBox(NULL, "�t�H���g�̓Ǎ����s", "", MB_OK); }

	//���Ԍv��
	LONGLONG nowTime;
	LONGLONG prevTime = nowTime = GetNowHiPerformanceCount();

	//�ҋ@�t���[������(60fps)
	float waitFrameTime = 16667.0f;

	//���C�����[�v�p�t���O�ϐ�
	bool loop = true;

	//���f���Ǘ��N���X�̐���
	ModelManager::GetInstance();

	//�T�E���h�Ǘ��N���X�̐���
	SoundManager::GetInstance();

	//���̃V�[��
	SceneType nowSceneType;

	//�ЂƂO�̃V�[��
	SceneType prevSceneType = nowSceneType = SceneType::TITLE;

	//�V�[���𐶐�
	SceneBase* sceneBase = new TitleScene();
	
	//���C�����[�v
	while (loop)
	{
		//�O�t���[���ƌ��݂̃t���[���̍���
		float deltaTime;

		//���݂̃t���[�����X�V
		nowTime = GetNowHiPerformanceCount();

		//������100������1�ɂ��ĕۑ�����(�}�C�N���b���Z)
		deltaTime = (nowTime - prevTime) / 1000000.0f;

		//�}�E�X�J�[�\����\�����Ȃ�
		SetMouseDispFlag(FALSE);

		//Dxlib�̃J������Effekseer�̃J�����𓯊�
		Effekseer_Sync3DSetting();

		KeyManager::GetInstance().Update();

		SoundManager::GetInstance().SeUpdate();

		//�e�V�[���̍X�V����
		nowSceneType = sceneBase->Update(deltaTime);

		//��ʂ�����������
		ClearDrawScreen();

		//�e�V�[���̕`�揈��
		sceneBase->Draw();

		//�f�o�b�N�p�@�f���^�^�C���v��
		DrawFormatString(0, 500, GetColor(255, 255, 255), "%f", deltaTime, TRUE);
		DrawFormatString(0, 550, GetColor(255, 255, 255), "%d", sceneBase->Get(), TRUE);


		//����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		//���̃V�[����END�Ȃ烁�C�����[�v�𔲂���
		if (nowSceneType == SceneType::END || CheckHitKey(KEY_INPUT_ESCAPE))
		{
			loop = false;
			break;
		}

		//���̃V�[�����O�̃V�[���ƈႤ�Ȃ�
		if (nowSceneType != prevSceneType)
		{
			delete sceneBase;									//�V�[���̉��
			sceneBase = sceneBase->CreateScene(nowSceneType);	//�V�����V�[���̐���
		}

		//���O�̃V�[�����L�^
		prevSceneType = nowSceneType;

		//60fps����p���[�v
		while (GetNowHiPerformanceCount() - nowTime < waitFrameTime);

		//���݂̃t���[����ۑ�
		prevTime = nowTime;
	}

	//�t�H���g�̍폜
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	delete sceneBase;		//�V�[���̉��

	Effkseer_End();			//Effekseer�̏I������

	DxLib_End();			//Dxlib�̏I������

	return 0;				//�\�t�g�̏I�� 
}