#ifndef FAIRY_H
#define FAIRY_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************

// �v���C���[�̉摜�̒萔
#define Fairy_TEX_W        (260)   // �v���C���[�̉摜1�̕�
#define Fairy_TEX_H        (290)   // �v���C���[�̉摜1�̍���
#define Fairy_PIVOT_X      (130)    // �v���C���[�̉������̒��S
#define Fairy_PIVOT_Y      (145)   // �v���C���[�̏c�����̉��[

#define GRAVITY             (1.0f)      // �d�͂̒萔
#define GROUND_Y            (640.0f)    // �n�ʂ̍����̒萔



//------< �֐� >----------------------------------------------------------------
void fairy_init();
void fairy_deinit();
void fairy_update();
void fairy_render();

#endif//PLAYER_H#pragma once