#ifndef FAIRY_H
#define FAIRY_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************

// プレイヤーの画像の定数
#define Fairy_TEX_W        (260)   // プレイヤーの画像1つの幅
#define Fairy_TEX_H        (290)   // プレイヤーの画像1つの高さ
#define Fairy_PIVOT_X      (130)    // プレイヤーの横方向の中心
#define Fairy_PIVOT_Y      (145)   // プレイヤーの縦方向の下端

#define GRAVITY             (1.0f)      // 重力の定数
#define GROUND_Y            (640.0f)    // 地面の高さの定数



//------< 関数 >----------------------------------------------------------------
void fairy_init();
void fairy_deinit();
void fairy_update();
void fairy_render();

#endif//PLAYER_H#pragma once