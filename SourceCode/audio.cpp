#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
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
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
