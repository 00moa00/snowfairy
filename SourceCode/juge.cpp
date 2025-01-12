#include "all.h"

extern OBJ2D bobj[BOBJ_MAX];
extern OBJ2D Fairy;
extern OBJ2D vase;
extern OBJ2D Maincloud;
extern OBJ2D Enemy[ENEMY_MAX];
extern int damage;


//static int breakcheck = 0;
 int LeftTimer , RightTimer ;


extern float cursor_posX;
extern float cursor_posY;




bool ha;  //オブジェクトを掴んでいるか判定する用の変数

using namespace  input;
using namespace DirectX;
using namespace GameLib;

//void BreakCheck() {
//    breakcheck++;
//}

void juge_init()
{
  
    ha = false;
   
}

void juge_deinit()
{
    
}

void juge_update()
{
    

    if (Fairy.isflag)
    {
        for (int i = 0; i < BOBJ_MAX; i++)
        {
            if (bobj[i].moveAlg != nullptr)   
            {
             
                //ここでカーソルとブロックオブジェクトが接触しているか判定する
                if (hanteiR(cursor_posX, bobj[i].pos.x,
                    PL_TEX_POS_X, bobj[i].texSize.x,
                    cursor_posY, bobj[i].pos.y,
                    PL_TEX_POS_Y, bobj[i].texSize.y)
                    )
                {
                    
                    if (((GetAsyncKeyState(VK_LBUTTON) < 0) || (GetAsyncKeyState(VK_SHIFT) < 0)))   //もしSHIFTキーがおされていたらposを代入する
                    {
                        //ha = true;
                        if(bobj[0].state == 0 && bobj[1].state == 0 && bobj[2].state == 0 && bobj[3].state == 0 && bobj[4].state == 0)
                        setstate(&bobj[i]);

                    }     
                    else
                    {
                        //ha = false;
                        offstate(&bobj[i]);


                    }


                    if (GetAsyncKeyState(MK_RBUTTON)) {
                        RightTimer++;
                        breakcheck(&bobj[i]);
                 
                    }

                }
              

                //ここで壺とブロックオブジェクトが接触しているか判定する
                if (hanteiR(vase.pos.x - VA_TEX_SIZE_X / 2, bobj[i].pos.x,
                    vase.texSize.x, bobj[i].texSize.x,
                    vase.pos.y - ((VA_TEX_SIZE_Y / 2) - 100), bobj[i].pos.y,
                    VA_TEX_SIZE_Y - 100, bobj[i].texSize.y)
                    )
                {

                    if(bobj[i].diff == KEN || bobj[i].diff == TATE || bobj[i].diff == GOMI2||bobj[i].diff == GOMI)  continue;

                    if (!hanteiR(vase.pos.x - VA_TEX_SIZE_X / 2, bobj[i].pos.x,
                        vase.texSize.x / 5, bobj[i].texSize.x,
                        vase.pos.y - ((VA_TEX_SIZE_Y / 2) - 80), bobj[i].pos.y,
                        VA_TEX_SIZE_Y - 80, bobj[i].texSize.y) &&
                        !hanteiR((vase.pos.x - VA_TEX_SIZE_X / 2) + 180, bobj[i].pos.x,
                            vase.texSize.x / 5, bobj[i].texSize.x,
                            vase.pos.y - ((VA_TEX_SIZE_Y / 2) - 80), bobj[i].pos.y,
                            VA_TEX_SIZE_Y - 80, bobj[i].texSize.y)
                        )
                    {

                        music::play(BGM_BLOCK);
                        flagdie(&bobj[i]);
                        vase_countup(bobj[i].diff);
                        
                    }
                }

            }

        }   //ここでBOBJのfor文の末端


        
        for (int i = 0; i < ENEMY_MAX; i++)
        {
            if (Enemy[i].moveAlg == nullptr || !Enemy[i].isflag) continue;

            //雲と敵が接触したら雲に攻撃 
            if (hanteiR(Enemy[i].pos.x, Maincloud.pos.x,
                Enemy[i].texSize.x, Maincloud.texSize.x,
                Enemy[i].pos.y, Maincloud.pos.y,
                Enemy[i].texSize.y, Maincloud.texSize.y/2)
                )
            {
                switch (Enemy[i].diff)
                {
                case BALLOON:
                    cloud_damek(Enemy[i].atacck);
                    Enemyflagdie(&Enemy[i]);
                    break;

                case BIRD:
                    if (Enemy[i].Aflag)
                    {
                        cloud_damek(Enemy[i].atacck);
                        Enemy[i].Aflag = false;
                    }
                    break;

                }
               
            }

            //泥棒と壺の接触判定
            if (Enemy[i].scale.x < 0.0f)
            {
                if (hanteiR(Enemy[i].pos.x - Enemy[i].texSize.x, (vase.pos.x - VA_TEX_SIZE_X / 2) + 50,
                    Enemy[i].texSize.x, vase.texSize.x - 100,
                    Enemy[i].pos.y, vase.pos.y - VA_TEX_SIZE_Y / 2,
                    Enemy[i].texSize.y, vase.texSize.y)
                    )
                {
                    switch (Enemy[i].diff)
                    {
                    case FLIGHT:
                        cloud_damek(Enemy[i].atacck);
                        break;
                    }

                }
            }
            else
            {
                if (hanteiR(Enemy[i].pos.x, (vase.pos.x - VA_TEX_SIZE_X / 2) + 50,
                    Enemy[i].texSize.x, vase.texSize.x - 100,
                    Enemy[i].pos.y, vase.pos.y - VA_TEX_SIZE_Y / 2,
                    Enemy[i].texSize.y, vase.texSize.y)
                    )
                {
                    switch (Enemy[i].diff)
                    {
                    case FLIGHT:
                        cloud_damek(Enemy[i].atacck);
                        break;
                    }

                }

            }

        }  //敵に関するfor文の末端


        
       // for (int i = 0; i < BOBJ_MAX; i++) {

            //敵と剣のブロックが接触したら消滅する

            if (bobj[4].diff == KEN) {
        for (int i = 0; i < ENEMY_MAX; i++)
        {
            if (Enemy[i].moveAlg != nullptr)
            {
                switch (Enemy[i].diff)
                {
                case FLIGHT:
                    if (Enemy[i].scale.x < 0.0f)
                    {
                        if (hanteiR(bobj[4].pos.x, Enemy[i].pos.x - Enemy[i].texSize.x,
                            bobj[4].texSize.x, Enemy[i].texSize.x,
                            bobj[4].pos.y, Enemy[i].pos.y,
                            bobj[4].texSize.y, Enemy[i].texSize.y
                        )) {

                            music::play(BGM_ATTACK);
                            Enemy_damage(&Enemy[i], bobj[4].atacck);
                            flagdie(&bobj[4]);
                            if (Enemy_ischeck(&Enemy[i])) Enemyflagdie(&Enemy[i]);
                        }
                    }
                    else
                    {
                        if (hanteiR(bobj[4].pos.x, Enemy[i].pos.x,
                            bobj[4].texSize.x, Enemy[i].texSize.x,
                            bobj[4].pos.y, Enemy[i].pos.y,
                            bobj[4].texSize.y, Enemy[i].texSize.y
                        )) {

                            music::play(BGM_ATTACK);
                            Enemy_damage(&Enemy[i], bobj[4].atacck);
                            flagdie(&bobj[4]);
                            if (Enemy_ischeck(&Enemy[i])) Enemyflagdie(&Enemy[i]);
                        }

                    }
                    break;
                default:
                    if (hanteiR(bobj[4].pos.x, Enemy[i].pos.x,
                        bobj[4].texSize.x, Enemy[i].texSize.x,
                        bobj[4].pos.y, Enemy[i].pos.y,
                        bobj[4].texSize.y, Enemy[i].texSize.y
                    )) {

                        music::play(BGM_ATTACK);
                        Enemy_damage(&Enemy[i], bobj[4].atacck);
                        flagdie(&bobj[4]);
                        if (Enemy_ischeck(&Enemy[i])) Enemyflagdie(&Enemy[i]);
                    }
                    break;
                }
            }
        }
                                      }

            //盾と雲が接触したらｈｐ回復
            if (bobj[4].diff == TATE) {
                if (hanteiR(bobj[4].pos.x, Maincloud.pos.x,
                    bobj[4].texSize.x, Maincloud.texSize.x,
                    bobj[4].pos.y, Maincloud.pos.y+ Maincloud.texSize.y / 2,
                    bobj[4].texSize.y, Maincloud.texSize.y / 2)
                    ) {
                    cloud_heal(bobj[4].defence);
                    flagdie(&bobj[4]);
                }

                if (hanteiR(bobj[4].pos.x, 1033,
                    bobj[4].texSize.x, 200,
                    bobj[4].pos.y, 45,
                    bobj[4].texSize.y, 40)
                    ) {
                    timer_heal(10);
                    flagdie(&bobj[4]);
                }
            }



            
       // }

    }
   
    //debug::setString("bool:%d", ha);
    //debug::setString("LeftTimer:%d", LeftTimer);
    //debug::setString("RightTimer:%d", RightTimer);
    //debug::setString("break:%d", breakcheck);
}

void juge_draw()
{
    
}

bool hantei(float pr, float er, float px, float ex, float py, float ey)
{
    
    float hankei = pr + er;
    float xzyuku = px - ex;
    float yzyuku = py - ey;

    if (hankei * hankei >= xzyuku * xzyuku + yzyuku * yzyuku)
    {
        return true;
    }
    else {
        return false;
    }
}

bool hanteiR(float x1, float x2, float gx1, float gx2, float y1, float y2, float gy1, float gy2)
{
    float left1, right1, top1, bottom1;
    float left2, right2, top2, bottom2;

    //1つ目の四角形のセット
    left1 = x1;
    right1 = x1 + gx1;
    top1 = y1;
    bottom1 = y1 + gy1;

    //2つ目の四角形のセット
    left2 = x2;
    right2 = x2 + gx2;
    top2 = y2;
    bottom2 = y2 + gy2;

    //座標や大きさは予めセットされているものとする
    if ((right1 > left2) && (left1 < right2) && (top1 < bottom2) && (bottom1 > top2))
    {
        return true;
    }
    else        
    return false;
}

