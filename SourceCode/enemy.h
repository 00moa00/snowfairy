#ifndef ENEMY_H
#define ENEMY_H

#include "all.h"


void enemy_init();
void enemy_deinit();
void enemy_update();
void enemy_render();

void Enemyflagdie(OBJ2D* obj);
void Enemy_damage(OBJ2D* obj, int a);
bool Enemy_ischeck(OBJ2D* obj);
void Enemy_anime_ballon(OBJ2D* obj, int koma);
void Enemy_anime_bird(OBJ2D* obj, int koma);
void Enemy_anime_diebird(OBJ2D* obj, int koma);
void Enemy_anime_thief(OBJ2D* obj, int koma);
void Enemy_anime_diethief(OBJ2D* obj, int koma);
void move_Balloon(OBJ2D* enemy);
void move_bird(OBJ2D* enemy);
void move_thief(OBJ2D* enemy);
#endif//Vase_H
