#ifndef Vase_H
#define Vase_H

#include "all.h"


void vase_init();
void vase_deinit();
int vase_update(Setdiff setdiff);
void vase_draw();

bool vase_check();
void vase_clear();
void vase_set(int nan);  //引数「nan」は難易度用の引数
void vase_countup(int diff);
void vase_move();  //雲と連動して動く処理



void vase_gomicheck();
#endif//Vase_H