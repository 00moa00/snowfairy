#include "all.h"


int snowm_state, snowm_timer;

//reset
int reset_texSizeX ;

//timer
int timer_texSizeX;
int timer_h;

extern int STAGE_NUM;
extern int rest;
extern int game_timer;

OBJ2D snowman;
Sprite* spr_reset;
Sprite* spr_reset_under;
Sprite* spr_timer;
Sprite* spr_timer_up;
Sprite* spr_clock;

struct SNOW_MAN {
    Sprite* spr;
    const wchar_t* filepath;
};

SNOW_MAN snowM_data[]{
    {NULL,L"./Data/Images/snowman/UIsnow.png"},
    {NULL,L"./Data/Images/snowman/UIsnow0.png"},
    {NULL,L"./Data/Images/snowman/UIsnow1.png"},
    {NULL,L"./Data/Images/snowman/UIsnow2.png"},
    {NULL,L"./Data/Images/snowman/UIsnow3.png"},
    {NULL,L"./Data/Images/snowman/UIsnow4.png"},

};


void snowman_init()
{
    snowm_timer = 0;
    snowm_state = 0;
}

void snowman_deinit()
{

    for (int i = 0; i < SNOWMAN_MAX; i++) {
        safe_delete(snowM_data[i].spr);
    }
    safe_delete(spr_reset);
    safe_delete(spr_reset_under);
    safe_delete(spr_timer);
    safe_delete(spr_timer_up);
    safe_delete(spr_clock);

}

bool snowman_update() 
{

    switch (snowm_state)
    {
    case 0:
        for (int i = 0; i < SNOWMAN_MAX; i++) {
            snowM_data[i].spr = sprite_load(snowM_data[i].filepath);
        }

        spr_reset = sprite_load(L"./Data/Images/reset1.png");
        spr_reset_under = sprite_load(L"./Data/Images/reset2.png");
        spr_timer = sprite_load(L"./Data/Images/timer.png");
        spr_timer_up = sprite_load(L"./Data/Images/timer_up.png");
        spr_clock = sprite_load(L"./Data/Images/clock.png");

        ++snowm_state;

    case 1:

        GameLib::setBlendMode(Blender::BS_ALPHA);
        ++snowm_state;
        timer_texSizeX = 200;
        timer_h = 0;

    case 2:

        reset_texSizeX = 225 - (RESET_SIZE * rest);
        if (STAGE_NUM < 3)
        {
            timer_texSizeX = (200 - (game_timer) / 7) + timer_h;
        }
        else if (STAGE_NUM <5) {
            timer_texSizeX = (200 - (game_timer) / 11) + timer_h;

        }
        else if (STAGE_NUM <7) {
            timer_texSizeX = (200 - (game_timer) / 13) + timer_h;

        }
     
       // timer_texSizeX += 100;

        if (timer_texSizeX <= 0) 
            return true;
        return false;

        break;
    }
   //debug::setString("rest2:%d", rest);
}
void snowman_render()
{
   sprite_render(
       snowM_data[STAGE_NUM].spr,
       25, 25,
       1, 1,
       0, 0,
       173, 179
   );

   sprite_render(
       spr_reset,
       (SCREEN_W / 2) - 123, 25,
       1, 1,
       0, 0,
       reset_texSizeX, 54
   );


   sprite_render(
       spr_reset_under,
       (SCREEN_W / 2) - 123, 25,
       1, 1,
       0, 0,
       225, 54
   );

   sprite_render(
       spr_timer,
       1033, 45,
       1, 1,
       0, 0,
       timer_texSizeX, 40
   );
   sprite_render(
       spr_timer_up,
       1033, 43,
       1, 1,
       0, 0,
       207, 45
   );
   sprite_render(
       spr_clock,
       972, 37,
       1, 1,
       0, 0,
       53, 56
   );
}

void timer_heal(int time) {
    if ((time + timer_texSizeX) > 200) {
        time = 200 - timer_texSizeX;
    }
    timer_h += time;
}