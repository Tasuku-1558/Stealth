#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "RepopEffect.h"

class Player;
class RepopEffect;

/// <summary>
/// �P�[�L�ƃo���b�g�Ǘ��N���X
/// �P�[�L�������Ă邩����ł邩�A�P�[�L�𔭎˂��Ǘ�
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePos);
    virtual ~CakeBullet();

    void Update(float deltaTime, Player* player,
                RepopEffect* cakeEffect);           //�X�V����

    void Draw();                                    //�`�揈��
    
    const bool CakeGet() { return cakeGet; }                      //�P�[�L���������Ă��邩���Ȃ�����Ԃ�

    Cake* cake;         //Cake�N���X�̃|�C���^
    Bullet* bullet;     //Bullet�N���X�̃|�C���^

private:

    void Initialize();                                               //����������
    void Activate();                                                 //����������
    void Finalize();                                                 //�I������
    void Shoot(float deltaTime, Player* player);                     //�o���b�g���ˏ���
    void BulletReuse(float deltaTime, RepopEffect* cakeEffect);      //�o���b�g�Ďg�p�J�E���g

    float bulletCount;                                               //�e�̌��ʎ���
    bool cakeGet;                                                    //�P�[�L���������Ă��邩���Ȃ���

};