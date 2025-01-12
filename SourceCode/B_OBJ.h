#ifndef B_OBJ_H
#define B_OBJ_H

#include "all.h"


void bobj_init();
void bobj_deinit();
void bobj_update();
void bobj_draw();

void obj_move0(OBJ2D* obj);  //�ޗ��n�I�u�W�F�N�g�̓��쏈��
void obj_move1(OBJ2D* obj);  //�U���I�u�W�F�N�g�̓��쏈��
void obj_move2(OBJ2D* obj);  //�h��I�u�W�F�N�g�̓��쏈��
void obj_move3(OBJ2D* obj);  //�S�~�I�u�W�F�N�g�̓��쏈��

void flagdie(OBJ2D* obj);              //�u���b�N�I�u�W�F�N�g�̃t���b�O�A�֐��|�C���^��null�ɂ���
void setstate(OBJ2D* obj);
void offstate(OBJ2D* obj);
void breakcheck(OBJ2D* obj);

#endif//B_OBJ_H

