#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

//------< ’è” >----------------------------------------------------------------
#define BGM_TITLE			0
#define BGM_GAME			1
#define BGM_BLOCK     2
#define BGM_ATTACK     3
#define BGM_HIT 4
#define BGM_CLEAR 5
#define BGM_GAMEOVER 6

//#define XWB_STAGE1_START   

//------< ŠÖ” >----------------------------------------------------------------
void audio_init();
void audio_deinit();

#endif//AUDIO_H
