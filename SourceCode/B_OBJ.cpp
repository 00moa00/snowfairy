#include "all.h"



int bobj_timer;
int bobj_state;
int rest;

extern int STAGE_NUM;
extern int Fairy_flag;

void Datanum(int num, int num_u) {
    int dataNum = num;
    int data_u_Num = num_u;
}

OBJ2D bobj[BOBJ_MAX];

//void delay(clock_t n);

struct BOBJ_DATA
{
    Sprite* spr;
    const wchar_t* filepath;      //画像用ファイルパス
    int atack;                    //攻撃力
    int defence;                  //防御力
    int diff;                     //オブジェクトの種類
    OBJ2D::FUNC_PTR movealg;       //オブジェクトの動作(関数ポインタ)

};


BOBJ_DATA bobj_data[] =
{ {NULL, L"./Data/Images/Block/block_trush.png", 0, 0, GOMI,obj_move3},    //ゴミのデータ
  {NULL, L"./Data/Images/Block/block_star.png", 0, 0, HOSI, obj_move0},   //星のデータ
  {NULL, L"./Data/Images/Block/block_diamond.png", 0, 0, DAIYA,obj_move0},   //ダイヤのデータ
  {NULL, L"./Data/Images/Block/block_heart.png", 0, 0, HERT, obj_move0},   //ハートのデータ
  {NULL, L"./Data/Images/Block/block_spade.png", 0, 0, SPAED, obj_move0},   //ハートのデータ
  {NULL, L"./Data/Images/Block/block_club.png", 0, 0, CLOBER, obj_move0},   //ハートのデータ
   
};


//5番目のブロックの設定   
BOBJ_DATA bobj_u_data[] =
{
    {NULL, L"./Data/Images/Block/block_sword2.png", 10, 0, KEN, obj_move1},   //剣のデータ
    {NULL, L"./Data/Images/Block/block_shield2.png", 0, 30, TATE,obj_move2},   //盾のデータ
    {NULL, L"./Data/Images/Block/block_trush.png", 0, 0, GOMI2,obj_move3},    //ゴミのデータ
};


void bobj_init()
{
    bobj_timer = 0;
    bobj_state = 0;
    rest = 0;
}

void bobj_deinit()
{

    //ブロック 0 ~ 3
    int dataNum = 0;
    if (STAGE_NUM < 2) {
        dataNum = STAGE_EASY_BOBJ;   //ブロックが何種類あるか決める
    }
    else {

        dataNum = STAGE_HARD_BOBJ;
    }

    for (int i = 0; i < dataNum; i++)
    {
        safe_delete(bobj_data[i].spr);
    }

    //ブロック 4
    int data_u_Num = sizeof(bobj_u_data) / sizeof(BOBJ_DATA);   //ブロックが何種類あるか決める
    for (int i = 0; i < data_u_Num; i++)
    {
        safe_delete(bobj_u_data[i].spr);
    }
}

void bobj_update()
{

    int dataNum = 0;
    if (STAGE_NUM < 3) {
        dataNum = STAGE_EASY_BOBJ;   //ブロックが何種類あるか決める
    }
    else {
        dataNum = STAGE_HARD_BOBJ;
    }


    int diff;   //ブロックの種類を決める用変数

    int data_u_Num = sizeof(bobj_u_data) / sizeof(BOBJ_DATA);   //ブロックが何種類あるか決める
    int diff_u;   //ブロックの種類を決める用変数

    switch (bobj_state)
    {
    case 0:              //オブジェクトランダム生成用ケース
        for (int i = 0; i < dataNum; i++)
            bobj_data[i].spr = sprite_load(bobj_data[i].filepath);  //アイコンがランダムで表示されるように毎回代入する画像を変更する

        for (int i = 0; i < data_u_Num; i++)
            bobj_u_data[i].spr = sprite_load(bobj_u_data[i].filepath);  //アイコンがランダムで表示されるように毎回代入する画像を変更する

        bobj_state++;
        /*fallthrou*/
    case 1:             //ランダムに生成されたオブジェクトのパラメーターを代入する
        for (int i = 0; i < BOBJ_MAX; i++)    //bobj内のデータクリア
        {
            bobj[i] = {};
        }

        //bobj内の固定数値設定
        for (int i = 0; i < BOBJ_MAX; i++)    
        {

            bobj[i].scale = { 1.0f, 1.0f };
            bobj[i].texSize = { 90.0f, 90.0f };
            bobj[i].pos = { 340.0f + (float)(120 * i), 100.0f };   //オブジェクトの初期表示座標設定箇所
        
        }

        bobj_state++;
        /*fallthrou*/

    case 2:            //オブジェクト生成後の各動作処理

        for (int i = 0; i < BOBJ_MAX; i++)
        {
            if (bobj[i].state == 0 &&(bobj[i].pos.x < 340 ||bobj[i].pos.x > SCREEN_W-(340+80) || bobj[i].pos.y < 100 || bobj[i].pos.y > SCREEN_H-(530+80))) {
                bobj[i].pos = VECTOR2(340.0f + (float)(120 * i), 100.0f);
            }


           if (bobj[i].moveAlg != nullptr && bobj[i].isflag)
            {
                (*bobj[i].moveAlg)(&bobj[i]);
                if (bobj[i].state == 1)                     //ジャッジ関数でプレイヤーカーソルとブロックが触れていれば
                {
                    bobj[i].pos = GetCposition();
                   

                }       //カーソルの座標を取得する関数を用意して代入する。返り値はVECTPOR2型
               // debug::setString("state[%d]:%d", i, bobj[i].state);
               
                continue;
            }

            for (int j = 0; j < BOBJ_MAX-1; j++) {

               
                int ran = rand() % 6;
                if (ran  > 0) {
                    diff = (rand() % (dataNum - 1)) + 1;
                }
                else {
                    diff = (rand() % (dataNum - 1));
                }
                

                if (bobj[j].timer <= 50)   //ランダム生成されるアニメーションの処理
                {
                    bobj[j].pos = VECTOR2(340.0f + (float)(120 * j), 100.0f);
                    bobj[j].isflag = true;
                    bobj[j].data = bobj_data[diff].spr;
                    bobj[j].timer++;
                    for (j = 0; j < 10000; j++) {}
                   // このfor文を利用することでブロックが左から順番に生成されていく
                  // for (j = 0; j < 4; j++) {} // 0ループを利用して遅延
                }

                //テスト用のオブジェクトリセット処理
                else  
                {
                    Set(&bobj[j],
                        BOBJ_MAX-1,
                        diff,
                        bobj_data[diff].movealg,
                        bobj_data[diff].atack,
                        bobj_data[diff].defence,
                        bobj_data[diff].spr);
                }


                //5番目のブロックのアニメ

                diff_u = rand() % (data_u_Num-1);

                ran = rand() % 3;
                if (ran  == 0) { data_u_Num += 1; } //ゴミブロックの出現の確率


                if (bobj[4].timer <= 100)   //ランダム生成されるアニメーションの処理
                {
                    bobj[4].pos = VECTOR2(340.0f + (float)(120 * 4), 100.0f);
                    bobj[4].isflag = true;
                    bobj[4].data = bobj_u_data[diff_u].spr;
                    bobj[4].timer++;
                   // bobj[4].diff = 10;

                }
                //テスト用のオブジェクトリセット処理
                else
                {
                    Set(&bobj[4],
                        1,
                        (10+diff_u),
                        bobj_u_data[diff_u].movealg,
                        bobj_u_data[diff_u].atack,
                        bobj_u_data[diff_u].defence,
                        bobj_u_data[diff_u].spr);
                }

            }


        }

        //ブロックのブレイク処理

        for (int i = 0; i < BOBJ_MAX; i++)
        {
            if (bobj[i].breakC > BREAK_POINT) {
                bobj[i].texPos = { 90.0f * 1, 0 };
            }

            if (bobj[i].breakC > BREAK_POINT*2) {
                bobj[i].texPos = { 90.0f * 2, 0 };
            }

            if (bobj[i].breakC > BREAK_POINT*3) {
               
                flagdie(&bobj[i]);
                bobj[i].texPos = { 90.0f * 0, 0 };
                //breakCが150を超えたらresetとtexposを戻す
            }
        }
        //reset処理

        if ((GetAsyncKeyState(VK_SPACE) & 1) && rest < 3)      //テスト用のオブジェクトリセット処理
        {
            for (int i = 0; i < BOBJ_MAX; i++)
            {
                bobj[i].moveAlg = nullptr;
                bobj[i].isflag = false;
                bobj[i].timer = 0;
                bobj[i].breakC = 0;
                bobj[i].texPos = { 90.0f * 0, 0 };
            }
            rest++;
        }


        break;
    }

   // debug::setString("stage_num:%d", STAGE_NUM);
   // debug::setString("rest:%d", rest);
   // debug::setString("spr:%d", (int)bobj_data[0].spr);
   // debug::setString("spr:%d", (int)bobj_u_data[0].spr);
    bobj_timer++;
}

void bobj_draw()
{
    for (int i = 0; i < BOBJ_MAX-1; i++)
    {
        if (bobj[i].isflag)
        {
            sprite_render(bobj[i].data,
                bobj[i].pos.x, bobj[i].pos.y,
                bobj[i].scale.x, bobj[i].scale.y,
                bobj[i].texPos.x, bobj[i].texPos.y,
                bobj[i].texSize.x, bobj[i].texSize.y,
                bobj[i].pivot.x, bobj[i].pivot.y);
        }
    }

    if (bobj[4].isflag)
    {
        sprite_render(bobj[4].data,
            bobj[4].pos.x, bobj[4].pos.y,
            bobj[4].scale.x, bobj[4].scale.y,
            bobj[4].texPos.x, bobj[4].texPos.y,
            bobj[4].texSize.x, bobj[4].texSize.y,
            bobj[4].pivot.x, bobj[4].pivot.y);
    }
}

void obj_move0(OBJ2D* obj)               //材料系オブジェクトの動作処理
{

    //if(juge_nabe())                     //ジャッジ関数でブロックと鍋が触れていればtrueを返す
    //obj->isflag = false;                     //isflagをfalseにする
    //obj->moveAlg = nullptr;
    //obj->timer = 0;


}


void obj_move1(OBJ2D* obj)              //攻撃オブジェクトの動作処理
{
}

void obj_move2(OBJ2D* obj)              //防御オブジェクトの動作処理
{
}

void obj_move3(OBJ2D* obj)              //ゴミオブジェクトの動作処理
{
}

void flagdie(OBJ2D* obj)
{

    obj->isflag = false;                     //isflagをfalseにする
    obj->moveAlg = nullptr;
    obj->timer = 0;
    obj->breakC = 0;
    obj->texPos = { 90.0f * 0, 0 };
    obj->state = 0;
}

void setstate(OBJ2D* obj)
{
    obj->state = 1;
}


void offstate(OBJ2D* obj)
{
    obj->state = 0;
}

void breakcheck(OBJ2D* obj)
{
    obj->breakC ++;
}

//void delay(clock_t n) {
//
//    clock_t start = clock();
//
//    while (clock() - start < n);
//
//}
