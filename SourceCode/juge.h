#ifndef JUGE_H
#define JUGE_H

#include "all.h"

//------< �v���g�^�C�v�錾 >-----------------------------------------------------
void juge_init();
void juge_deinit();
void juge_update();
void juge_draw();
bool hantei(float pr, float er, float px, float ex, float py, float ey);  //�����蔻��̃v���O����
bool hanteiR(float x1, float x2, float gx1, float gx2, float y1, float y2, float gy1, float gy2);  //�����蔻��l�p�`

#endif//JUGE_H
