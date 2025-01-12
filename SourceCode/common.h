#ifndef COMMON_H
#define COMMON_H
			 
#define SCREEN_W	1280
#define SCREEN_H	720

#define SCENE_NONE		-1
#define SCENE_TITLE		0
#define SCENE_GAME		1
#define SCENE_GAME_OVER 2
#define SCENE_SCORE     3
#define SCENE_GAME_CLEAR 4

#define BOBJ_MAX 5

#define PL_HANKEI      (18) //プレイヤーの画像が○×○なので半径○の円として扱う
#define BO_HANKEI      (45) //ブロックオブジェクトの半径
#define VA_HANKEI      (125) //壺の半径

#define PL_TEX_POS_X    (35)
#define PL_TEX_POS_Y    (55)
#define PL_TEX_SIZE_X   (64)
#define PL_TEX_SIZE_Y   (64)
#define PL_TEX_PIVOT_X  (32)
#define PL_TEX_PIVOT_Y  (32)
#define PL_SCALE_X      (1.0f)
#define PL_SCALE_Y      (1.0f)
#define VA_TEX_SIZE_X   (243)
#define VA_TEX_SIZE_Y   (260)

//fiary
#define FAIRY_POS ((SCREEN_H/2)+50)
#define FAIRY_TEX_SIZE_X (113)
#define FAIRY_TEX_SIZE_Y (166)
#define FAIRY_SERIHU_MAX 12

#define MCLOUD_POSY ((SCREEN_H/2)+50)

//enemy
#define ENEMY_MAX (3)

//break
#define BREAK_POINT 20

//stage
#define STAGE_EASY_BOBJ 4
#define STAGE_HARD_BOBJ 6

//snowman
#define SNOWMAN_MAX 6

//reset
#define RESET_SIZE 75

#define RANK_MAX 4



extern int CurScene;
extern int nextScene ;

enum Block
{
    GOMI = 0,
    HOSI,
    DAIYA,
    HERT,
    SPAED,
    CLOBER,
    
};
enum Block2
{
    KEN = 10,
    TATE,
    GOMI2,

};

enum Enemy
{
    BIRD = 0,
    BALLOON,
    FLIGHT
};

enum Enemy_bird
{
    bird_init = 0,
    bird_moveL_init,
    bird_moveL,
    bird_moveR_init,
    bird_moveR,
    bird_atc_init,
    bird_atc,
    bird_atc_Ainit,
    bird_atc_A,
    bird_atcr_init,
    bird_atcr,
    bird_diemove_init,
    bird_diemove

};

enum Enemy_thief
{
    thief_init = 0,
    thief_moveL_init,
    thief_moveL,
    thief_moveR_init,
    thief_moveR,
    thief_atc_init,
    thief_atc,
    thief_atc_Ainit,
    thief_atc_A,
    thief_atcr_init,
    thief_atcr,
    thief_diemove_init,
    thief_diemoveL_init,
    thief_diemoveL,
    thief_diemoveR_init,
    thief_diemoveR

};


enum Diff
{
    EAZY = 3,
    NORMAL,
    HARD

};

struct Setdiff
{
    int diff;  //難易度
    int set_ho;     //星の必要個数
    bool set_ho_f;  //星をtrueにするかどうか
    int set_he;
    bool set_he_f;
    int set_da;
    bool set_da_f;
    int set_cl;
    bool set_cl_f;
    int set_sp;
    bool set_sp_f;

};

#endif