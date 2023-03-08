#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "PreCompiledHeader.h"
#include "ModelManager.h"
#include "DeltaTime.h"
#include "KeyManager.h"
#include "SoundManager.h"

#include "TitleScene.h"
#include "StageSelection.h"
#include "FirstStage.h"
#include "ResultScene.h"


//�V�����V�[���𐶐�����
SceneBase* CreateScene(SceneType nowScene)
{
	SceneBase* retScene = nullptr;

	switch (nowScene)
	{
	case SceneType::TITLE:
		retScene = new TitleScene;
		break;

	case SceneType::SELECTION:
		retScene = new StageSelection;
		break;

	case SceneType::PLAY:
		retScene = new FirstStage;
		break;

	case SceneType::RESULT:
		retScene = new ResultScene;
		break;
	}

	return retScene;
}

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
	if (Effekseer_Init(8000) == -1)
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

	//// �V���h�E�}�b�v�n���h���̍쐬
	//int shadowMapHandle = MakeShadowMap(SHADOWMAP_SIZE_X, SHADOWMAP_SIZE_Y);

	//// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	//SetShadowMapLightDirection(shadowMapHandle, LIGHT_DIRECTION);

	//// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	//SetShadowMapDrawArea(shadowMapHandle, SHADOWMAP_MINPOSITION, SHADOUMAP_MAXPOSITION);
	
	//�t�H���g�̓ǂݍ���
	LPCSTR fontPath = "Data/Font/Oranienbaum.ttf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {}
	else { MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK); }

	//���Ԍv��
	LONGLONG nowTime;
	LONGLONG prevTime = nowTime = GetNowHiPerformanceCount();

	//�ҋ@�t���[������(60fps)
	float waitFrameTime = 16667.0f;
	
	//���f���Ǘ��N���X�̐���
	ModelManager::GetInstance();

	//�T�E���h�Ǘ��N���X�̐���
	SoundManager::GetInstance();

	// �ЂƂO�̃V�[��
	SceneType prevSceneType = SceneType::TITLE;
	// ���̃V�[��
	SceneType nowSceneType = SceneType::TITLE;

	// �V�[���𐶐�
	SceneBase* sceneBase = new TitleScene();
	
	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�O�t���[���ƌ��݂̃t���[���̍���
		float deltaTime;

		//���݂̃t���[�����X�V
		nowTime = GetNowHiPerformanceCount();

		//������100������1�ɂ��ĕۑ�����(�}�C�N���b���Z)
		deltaTime = (nowTime - prevTime) / 1000000.0f;

		//Dxlib�̃J������Effekseer�̃J�����𓯊�
		Effekseer_Sync3DSetting();

		KeyManager::GetInstance().Update();

		SoundManager::GetInstance().SeUpdate();

		nowSceneType = sceneBase->Update(deltaTime);		//�e�V�[���̍X�V����

		//��ʂ�����������
		ClearDrawScreen();

		//// �V���h�E�}�b�v�ւ̕`��̏���
		//ShadowMap_DrawSetup(shadowMapHandle);

		//// �V���h�E�}�b�v�ւ̕`����I��
		//ShadowMap_DrawEnd();


		//// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
		//SetUseShadowMap(0, shadowMapHandle);

		//// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
		//SetUseShadowMap(0, -1);

		sceneBase->Draw();     //�e�V�[���̕`�揈��

		//�f�o�b�N�p�@�f���^�^�C���v��
		DrawFormatString(0, 500, GetColor(255, 255, 255), "%f", deltaTime, TRUE);

		//����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		//���̃V�[����END�Ȃ�
		if (nowSceneType == SceneType::END)
		{
			break;
		}

		if (nowSceneType != prevSceneType)
		{
			delete sceneBase; //�V�[���̉��
			sceneBase = CreateScene(nowSceneType);	//�V�[���̐���
		}

		//���O�̃V�[�����L�^
		prevSceneType = nowSceneType;

		//60fps����p���[�v
		while (GetNowHiPerformanceCount() - nowTime < waitFrameTime);

		//���݂̃t���[����ۑ�
		prevTime = nowTime;
	}

	//�t�H���g�̃A�����[�h
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {}
	else { MessageBox(NULL, "remove failure", "", MB_OK); }

	//DeleteShadowMap(shadowMapHandle);	//�V���h�E�}�b�v�̍폜

	delete sceneBase;

	Effkseer_End();				//Effekseer�̏I������

	DxLib_End();				//Dxlib�̏I������

	return 0;					//�\�t�g�̏I�� 
}