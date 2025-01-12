#include "all.h"



int     Fairy_state, Fairy_timer;
float   Fairy_speed;

int  Fairy_flag = 0;

//float Fairy

OBJ2D   Fairy;


struct FAIRY_SERIHU {
    Sprite* spr;
    const wchar_t* filepath;
};

FAIRY_SERIHU fairy_Sdata[]{
    {NULL, L"./Data/Images/Serihu/serihu1.png"},
    {NULL, L"./Data/Images/Serihu/serihu2.png"},
    {NULL, L"./Data/Images/Serihu/serihu3.png"},
    {NULL, L"./Data/Images/Serihu/serihu4.png"},
    {NULL, L"./Data/Images/Serihu/serihu5.png"},
    {NULL, L"./Data/Images/Serihu/serihu6.png"},
    {NULL, L"./Data/Images/Serihu/serihu7.png"},
    {NULL, L"./Data/Images/Serihu/serihu8.png"},
    {NULL, L"./Data/Images/Serihu/serihu9.png"},
    {NULL, L"./Data/Images/Serihu/serihu10.png"},
    {NULL, L"./Data/Images/Serihu/serihu11.png"},
    {NULL, L"./Data/Images/Serihu/serihu12.png"},


};


void fairy_init()
{
    Fairy_timer = 0;
    Fairy_state = 0;
    
}


void fairy_deinit()
{
    safe_delete(Fairy.data);
    
    for (int i = 0; i < FAIRY_SERIHU_MAX ; i++) {
        safe_delete(fairy_Sdata[i].spr);
    }
}

void fairy_update()
{
    switch (Fairy_state)
    {
    case 0:

         Fairy.data = sprite_load(L"./Data/Images/Fairy.png");
         for (int i = 0; i < FAIRY_SERIHU_MAX; i++) {
             fairy_Sdata[i].spr = sprite_load(fairy_Sdata[i].filepath);
         }
        ++Fairy_state;
        /*fallthrough*/

    case 1:
        //11.9’Ç‰Á•ª
        Fairy.isflag = true;

        Fairy_speed = 0.1f;

        Fairy.pos = { (SCREEN_W / 2)+240, FAIRY_POS };
        Fairy.scale = { 1.0f, 1.0f };
        Fairy.texSize = { FAIRY_TEX_SIZE_X, FAIRY_TEX_SIZE_Y };
        Fairy.pivot = { FAIRY_TEX_SIZE_X / 2, FAIRY_TEX_SIZE_Y / 2 };


        ++Fairy_state;
        /*fallthrough*/

    case 2:

        Fairy.pos.y += Fairy_speed;

        if (Fairy.pos.y >= ( FAIRY_POS + 5))
        {
            Fairy_speed *= -1;
        }

        if (Fairy.pos.y <= FAIRY_POS)
        {
            Fairy_speed *= -1;
        }

        break;



      //  debug::setString("OBj2D:%d", sizeof(OBJ2D));


        break;
    }
}

//--------------------------------------
//  ƒvƒŒƒCƒ„[‚Ì•`‰æ
//--------------------------------------
void fairy_render()
{

    sprite_render(
        Fairy.data,
        Fairy.pos.x,     Fairy.pos.y,
        Fairy.scale.x,   Fairy.scale.y,
        Fairy.texPos.x,  Fairy.texPos.y,
        Fairy.texSize.x, Fairy.texSize.y,
        Fairy.pivot.x,   Fairy.pivot.y
    );

    for (int i = 0; i < FAIRY_SERIHU_MAX; i++) {
        if (Fairy_flag == i) {
            sprite_render(
                fairy_Sdata[i].spr,
                0, 0,
                1, 1,
                0, 0,
                1280, 720
            );
        }
    }
}
