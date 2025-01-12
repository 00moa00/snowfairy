#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���
    music::load(BGM_TITLE, L"./Data/Sounds/bgm1.wav");
    music::load(BGM_GAME, L"./Data/Sounds/bgm2.wav");

    music::load(BGM_BLOCK, L"./Data/Sounds/bgm_block.wav");   
    music::load(BGM_ATTACK, L"./Data/Sounds/bgm_attack.wav");    

    music::load(BGM_HIT, L"./Data/Sounds/bgm_attack.wav");

    music::load(BGM_CLEAR, L"./Data/Sounds/stageclear.wav");
    music::load(BGM_GAMEOVER, L"./Data/Sounds/gameover.wav");




   // sound::setVolume(XWB_STAGE1,, 0.1f);
}

//--------------------------------------
//  �I�[�f�B�I�̏I������
//--------------------------------------
void audio_deinit()
{
    // ���y��S�ĉ��
    music::clear();
}
