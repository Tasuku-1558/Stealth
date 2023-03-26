#pragma once

#include <string>

using namespace std;

/// <summary>
/// �w�i����N���X
/// </summary>
class BackGround final
{
public:
    BackGround();
    virtual ~BackGround();

    void Update();              //�X�V����
    void Draw();                //�`�揈��

private:
    BackGround(const BackGround&);      //�R�s�[�R���X�g���N�^

    void Initialize();          //����������
    void Finalize();            //�I������

    int backGroundHandle;       //�w�i����i�[�p

    //�萔
    const string VIDEO_FOLDER_PATH;	        //Video�t�H���_�܂ł̃p�X
    const string BACKGROUND_VIDEO_PATH;	    //�w�i����̃p�X
    const int    PLAY_POSITION;             //����Đ��ʒu

};