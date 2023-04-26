#pragma once

#include "DxLib.h"
#include "Cake.h"
#include "Bullet.h"
#include "EffectManager.h"


/// <summary>
/// �P�[�L�o���b�g�N���X
/// �P�[�L�������Ă邩����ł邩�A�P�[�L�𔭎˂��Ǘ�
/// </summary>
class CakeBullet final
{
public:

    CakeBullet(const VECTOR& cakePosition, EffectManager* const inEffect, VECTOR playerPosition);
    virtual ~CakeBullet();

    void Update(float deltaTime);                   //�X�V����
    void Draw();                                    //�`�揈��
    
    const bool CakeGet() { return cakeGet; }        //�P�[�L���������Ă��邩���Ȃ�����Ԃ�

    Cake* cake;                                     //Cake�N���X�̃|�C���^
    Bullet* bullet;                                 //Bullet�N���X�̃|�C���^

private:

    void Shoot(float deltaTime);                    //�o���b�g���ˏ���
    void BulletReuse(float deltaTime);              //�o���b�g�Ďg�p�J�E���g

    EffectManager* effectManager;                   //EffectManager�N���X�̃|�C���^

    float bulletCount;                              //�e�̌��ʎ���
    bool cakeGet;                                   //�P�[�L���������Ă��邩���Ȃ���

    //�萔
    const float RESPAWN_EFFECT_POP_COUNT;           //���X�|�[���G�t�F�N�g�o���J�E���g
    const float MAX_BULLET_TIME;                   //�e�̍ő���ʎ���

};