#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "HitChecker.h"
#include "CakeRepopEffect.h"

class CakeRepopEffect;

/// <summary>
/// �P�[�L�ƃo���b�g�Ǘ��N���X
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePos);
    virtual ~CakeBullet();

    void Update(float deltaTime, const VECTOR& playerPos, 
                HitChecker* hitChecker, CakeRepopEffect* cakeEffect); //�X�V����

    void Initialize();          //����������
    void Activate();            //����������
    void Finalize();            //�I������
    void Draw();                //�`�揈��
    
    const bool CakeGet() { return cakeGet; }                        //�P�[�L���������Ă��邩���Ȃ�����Ԃ�

    Cake* cake;
    Bullet* bullet;

private:

    void Shoot(float deltaTime, const VECTOR& playerPos);            //�o���b�g���ˏ���
    void BulletReuse(float deltaTime, CakeRepopEffect* cakeEffect);  //�o���b�g�Ďg�p�J�E���g

    float bulletCount;                                               //�e�̌��ʎ���
    bool cakeGet;                                                    //�P�[�L���������Ă��邩���Ȃ���
    int	locateSe;				                                     //�P�[�L��u��������SE���i�[�p


    //�萔
    const std::string SOUND_FOLDER_PATH;		//sound�t�H���_�܂ł̃p�X
    const std::string LOCATE_SE_PATH;		    //�P�[�L��u��������SE���̃p�X

};