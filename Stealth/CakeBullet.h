#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "EffectManager.h"
#include "Player.h"
#include <vector>

/// <summary>
/// �P�[�L�ƃo���b�g�Ǘ��N���X
/// �P�[�L�������Ă邩����ł邩�A�P�[�L�𔭎˂��Ǘ�
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(/*const VECTOR& cakePosition,*/ EffectManager* const inEffect);
    virtual ~CakeBullet();

    void Update(float deltaTime, Player* player);   //�X�V����
    void Draw();                                    //�`�揈��
    
    const bool CakeGet() { return cakeGet; }        //�P�[�L���������Ă��邩���Ȃ�����Ԃ�
    std::vector<Cake*> cake;
    //Cake* cake;                                     //Cake�N���X�̃|�C���^
    Bullet* bullet;                                 //Bullet�N���X�̃|�C���^
    EffectManager* effectManager;                   //EffectManager�N���X�̃|�C���^

private:

    void Shoot(float deltaTime, Player* player);    //�o���b�g���ˏ���
    void BulletReuse(float deltaTime);              //�o���b�g�Ďg�p�J�E���g
    void EntryCake(Cake* newCake);		//�P�[�L��o�^
    void DeleteCake(Cake* deleteCake);	//�P�[�L���폜
    void CakePop();						//�P�[�L�̏o��


    float bulletCount;                              //�e�̌��ʎ���
    bool cakeGet;                                   //�P�[�L���������Ă��邩���Ȃ���

};