#ifndef B_OBJ_H
#define B_OBJ_H

#include "all.h"


void bobj_init();
void bobj_deinit();
void bobj_update();
void bobj_draw();

void obj_move0(OBJ2D* obj);  //材料系オブジェクトの動作処理
void obj_move1(OBJ2D* obj);  //攻撃オブジェクトの動作処理
void obj_move2(OBJ2D* obj);  //防御オブジェクトの動作処理
void obj_move3(OBJ2D* obj);  //ゴミオブジェクトの動作処理

void flagdie(OBJ2D* obj);              //ブロックオブジェクトのフラッグ、関数ポインタをnullにする
void setstate(OBJ2D* obj);
void offstate(OBJ2D* obj);
void breakcheck(OBJ2D* obj);

#endif//B_OBJ_H

