#ifndef SCENE_GAME_H
#define SCENE_GAME_H


void game_init();
void game_deinit();
void game_update();
void game_render();

void game_Mmove();
int rand_r(int min, int max);
bool R_mouse();

VECTOR2 GetCposition();

#endif 
#pragma once
