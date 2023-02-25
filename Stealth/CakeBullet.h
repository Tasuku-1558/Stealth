#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "HitChecker.h"
#include "RepopEffect.h"

class RepopEffect;

using namespace std;

/// <summary>
/// �P�[�L�ƃo���b�g�Ǘ��N���X
/// �P�[�L�������Ă邩����ł邩�A�P�[�L�𔭎˂��Ǘ�
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePos);
    virtual ~CakeBullet();

    void Initialize();          //����������
    void Activate();            //����������
    void Finalize();            //�I������

    void Update(float deltaTime, const VECTOR& playerPos,
                HitChecker* hitChecker, RepopEffect* cakeEffect); //�X�V����

    void Draw();                //�`�揈��
    
    const bool CakeGet() { return cakeGet; }                        //�P�[�L���������Ă��邩���Ȃ�����Ԃ�

    Cake* cake;         //Cake�N���X�̃|�C���^
    Bullet* bullet;     //Bullet�N���X�̃|�C���^

private:

    void Shoot(float deltaTime, const VECTOR& playerPos);            //�o���b�g���ˏ���
    void BulletReuse(float deltaTime, RepopEffect* cakeEffect);      //�o���b�g�Ďg�p�J�E���g

    float bulletCount;                                               //�e�̌��ʎ���
    bool cakeGet;                                                    //�P�[�L���������Ă��邩���Ȃ���
    int	locateSe;				                                     //�P�[�L��u��������SE���i�[�p

    //�萔
    const string SOUND_FOLDER_PATH;		//sound�t�H���_�܂ł̃p�X
    const string LOCATE_SE_PATH;		//�P�[�L��u��������SE���̃p�X

};