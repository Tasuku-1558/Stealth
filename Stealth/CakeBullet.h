#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "Player.h"
#include "EffectManager.h"


/// <summary>
/// �P�[�L�o���b�g�N���X
/// �P�[�L�������Ă邩����ł邩�A�P�[�L�𔭎˂��Ǘ�
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, Player* const inPlayer);
    virtual ~CakeBullet();

    void Update(float deltaTime);                   //�X�V����
    void Draw();                                    //�`�揈��
    
    const bool CakeGet() { return cakeGet; }        //�P�[�L���������Ă��邩���Ȃ�����Ԃ�

    Cake* cake;                                     //Cake�N���X�̃|�C���^
    Bullet* bullet;                                 //Bullet�N���X�̃|�C���^

private:
    CakeBullet(const CakeBullet&);                  //�R�s�[�R���X�g���N�^

    void CakeViability();                           //�P�[�L�̐���
    void Shoot(float deltaTime);                    //�o���b�g���ˏ���
    void BulletReuse(float deltaTime);              //�o���b�g�Ďg�p�J�E���g

    Player* player;                                 //Player�N���X�̃|�C���^
    EffectManager* effectManager;                   //EffectManager�N���X�̃|�C���^

    float bulletCount;                              //�e�̌��ʎ���
    bool cakeGet;                                   //�P�[�L���������Ă��邩���Ȃ���

    //�萔
    const float RESPAWN_EFFECT_POP_TIME;            //���X�|�[���G�t�F�N�g�̏o������
    const float MAX_BULLET_TIME;                    //�e�̍ő���ʎ���
    const float INITIAL_BULLET_TIME;                //�����̒e�̌��ʎ���

};