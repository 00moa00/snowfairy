#ifndef Vase_H
#define Vase_H

#include "all.h"


void vase_init();
void vase_deinit();
int vase_update(Setdiff setdiff);
void vase_draw();

bool vase_check();
void vase_clear();
void vase_set(int nan);  //�����unan�v�͓�Փx�p�̈���
void vase_countup(int diff);
void vase_move();  //�_�ƘA�����ē�������



void vase_gomicheck();
#endif//Vase_H