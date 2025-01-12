#include "Vase.h"

#define VASE_POS ((SCREEN_H/2)+50)

OBJ2D vase;

int vase_timer, vase_state;
int vase_daiya, vase_hosi, vase_heart, vase_spaed, vase_clober;            //壺に何個入ったカウントするようの変数
bool vase_daiya_c, vase_hosi_c, vase_heart_c, vase_spaed_c, vase_clober_c;  //クリア条件の数を代入する用の変数

int STAGE_NUM = 0; 
//float vase_posY;
float vase_speed;

extern int Fairy_flag;
extern OBJ2D Enemy[ENEMY_MAX];
extern int game_timer;

void vase_init()
{
    vase_timer = 0;
    vase_state = 0;
    vase_daiya = 0;
    vase_hosi = 0;
    vase_heart = 0;
    vase_spaed = 0;
    vase_clober = false;
    vase_daiya_c = false;
    vase_hosi_c = false;
    vase_heart_c = false;
    vase_spaed_c = false;
    vase_clober_c = false;

  //  STAGE_NUM = 0;
}

void vase_deinit()
{
    safe_delete(vase.data);
}

int vase_update(Setdiff setdiff)
{
    switch (vase_state)
    {
    case 0:
        vase.data = sprite_load(L"./Data/Images/kama.png");

        vase_state++;
        /*fallthrough*/

    case 1:
        //vase_posY = VASE_POS;
        vase_speed = 0.1f;


        vase.pos = { SCREEN_W / 2, VASE_POS };
        vase.scale = { 1.0f, 1.0f };
        vase.texSize = { VA_TEX_SIZE_X, VA_TEX_SIZE_Y };
        vase.pivot = { VA_TEX_SIZE_X / 2, VA_TEX_SIZE_Y / 2 };

        vase_state++;
        /*fallthrough*/

    case 2: //ステージ1の設定
        vase_daiya = setdiff.set_da;
        vase_daiya_c = setdiff.set_da_f;
        vase_hosi = setdiff.set_ho;
        vase_hosi_c = setdiff.set_ho_f;
        vase_heart = setdiff.set_he;
        vase_heart_c = setdiff.set_he_f;
        vase_clober = setdiff.set_cl;
        vase_clober_c = setdiff.set_cl_f;
        vase_spaed = setdiff.set_sp;
        vase_spaed_c = setdiff.set_sp_f;


        vase_state++;
        /*fallthrough*/

    case 3: //ステージ1の処理


        vase_gomicheck();

        if (STAGE_NUM == 0 && Fairy_flag == 11 && (TRG(0) & PAD_START)) {
            vase_clear();
            game_timer = 0;
            Fairy_flag += 1;
            STAGE_NUM = 1;
            for (int j = 0; j < ENEMY_MAX; j++) {
                Enemyflagdie(&Enemy[j]);
            }
           // set_diff[];
            

            music::stop(BGM_TITLE);
            music::play(BGM_GAME);
            music::setVolume(BGM_GAME, 0.2f);

            return SCENE_SCORE;
        }


        
        if (vase_check() && (STAGE_NUM !=0))
        {
            vase_clear();
            //stage_clear();  //ステージクリア時にシーンを移行する関数
           // vase_state = 1;

            STAGE_NUM++;


            for (int j = 0; j < ENEMY_MAX; j++) {
                Enemyflagdie(&Enemy[j]);
            }
            return SCENE_SCORE;
        }




        vase_move();
        //debug::setString("vase_daiya:%d", vase_daiya);
        //debug::setString("vase_hosi:%d", vase_hosi);
        //debug::setString("vase_heart:%d", vase_heart);
        //debug::setString("vase_clober:%d", vase_clober);
        //debug::setString("vase_spaed:%d", vase_spaed);

        break;

    }

    return 0;
}

void vase_draw()
{
    sprite_render(
        vase.data,
        vase.pos.x, vase.pos.y,
        vase.scale.x, vase.scale.y,
        vase.texPos.x, vase.texPos.y,
        vase.texSize.x, vase.texSize.y,
        vase.pivot.x, vase.pivot.y
    );
}

bool vase_check()
{

    if (vase_daiya <= 0 &&
        vase_hosi <= 0 &&
        vase_heart <= 0 &&
        vase_clober <= 0 &&
        vase_spaed <= 0)
    {
        return true;
    }

    return false;
}

void vase_gomicheck() {

    if (vase_daiya < 0 || vase_hosi < 0 || vase_heart < 0 || vase_clober < 0 || vase_spaed < 0) {
        cloud_damek(20);
        if(vase_daiya < 0) vase_daiya = 0;
        if(vase_hosi  < 0) vase_hosi = 0;
        if(vase_heart < 0) vase_heart = 0;
        if(vase_clober < 0) vase_clober = 0;
        if(vase_spaed < 0) vase_spaed = 0;
    }
}

void vase_clear()
{
    vase_daiya = 0;
    vase_hosi = 0;
    vase_heart = 0;
    vase_spaed = 0;
    vase_clober = 0;


   

}

void vase_set(int nan)
{

}

void vase_countup(int diff)
{
    switch (diff)
    {
    case HOSI:
       // if (vase_hosi > 0)
            vase_hosi--;
        break;
    case DAIYA:
        //if (vase_daiya > 0)
            vase_daiya--;
        break;
    case HERT:
        //if (vase_heart > 0)
            vase_heart--;
        break;
    case SPAED:
        //if (vase_spaed > 0)
            vase_spaed--;
        break;
    case CLOBER:
        //if (vase_clober > 0)
            vase_clober--;
        break;

    }

}

void vase_move()
{
    vase.pos.y += vase_speed;

    if (vase.pos.y >= (VASE_POS + 5))
    {
        vase_speed *= -1;
    }

    if (vase.pos.y <= VASE_POS)
    {
        vase_speed *= -1;
    }
}
