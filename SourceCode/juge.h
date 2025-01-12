#ifndef JUGE_H
#define JUGE_H

#include "all.h"

//------< プロトタイプ宣言 >-----------------------------------------------------
void juge_init();
void juge_deinit();
void juge_update();
void juge_draw();
bool hantei(float pr, float er, float px, float ex, float py, float ey);  //当たり判定のプログラム
bool hanteiR(float x1, float x2, float gx1, float gx2, float y1, float y2, float gy1, float gy2);  //当たり判定四角形

#endif//JUGE_H
