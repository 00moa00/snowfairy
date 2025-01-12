#include "all.h"


int game_state, game_timer;

//cursor
float cursor_posX, cursor_posY;
int cursor_texPosX_g,cursor_timer_g;
int hammer_texPosX, hammer_timer;

//snowing
float snowing_posY,snowing_speed;

extern int STAGE_NUM;
extern int Fairy_flag;
extern OBJ2D Enemy[ENEMY_MAX];

//Sprite* spr_BACK;
//Sprite* spr_BACKCLOUD;
//Sprite* spr_BACK_UNDER;

//OBJ2D* BACK[];
//OBJ2D* UNDER[];

Sprite* spr_CURSOR;
Sprite* spr_H_CURSOR;
Sprite* spr_snowing;

struct KUMO_DATA{
	Sprite* spr;
	const wchar_t* filepath;     
};

KUMO_DATA main_data[]{
	{ NULL, L"./Data/Images/Back/0.png"},
	{ NULL, L"./Data/Images/Back/1.png"},
	{ NULL, L"./Data/Images/Back/2.png"},
	{ NULL, L"./Data/Images/Back/3.png"},
	{ NULL, L"./Data/Images/Back/4.png"},
	{ NULL, L"./Data/Images/Back/5.png"},
	{ NULL, L"./Data/Images/Back/5.png"},
};

KUMO_DATA under_data[]{
	{ NULL, L"./Data/Images/Back/00.png"},
	{ NULL, L"./Data/Images/Back/11.png"},
	{ NULL, L"./Data/Images/Back/22.png"},
	{ NULL, L"./Data/Images/Back/33.png"},
	{ NULL, L"./Data/Images/Back/44.png"},
	{ NULL, L"./Data/Images/Back/55.png"},
	{ NULL, L"./Data/Images/Back/55.png"},
};

//startイメージ
Sprite* spr_start;

POINT po;

HWND hwnd;


Setdiff set_diff[] = { 

	//stage 0
	{ 
		EAZY,	//テュートリアル
	    1, true, //星
	    1, true, //ハート
	    1, true, //ダイア
	    0, false, //クローバー
	    0, false	 //スペード
	},

	//stage 1
	{
		EAZY,
		2, true,
		rand_r(2,3), true, //ハート
		rand_r(3,4), true, //ダイア
		0, false,
		0, false,
		//min 4 max6
	},

	{
		EAZY,
		rand_r(3,4), true,
		rand_r(3,4), true,
		rand_r(3,4), true,
		0, false,
		0, false,
		//min 6 max 9
	},

	{
		EAZY,
		2, true,
		rand_r(3,4), true,
		3, true,
		rand_r(1,3), true,
		rand_r(3,5), true,
		//min 8 max 12
	},

	{
		EAZY,
		3, true,
		rand_r(3,4), true,
		rand_r(3,5), true,
		5, true,
		4, true,
		//min 11 max 15
	},

	{
		EAZY,
		rand_r(3,4), true,
		rand_r(4,5), true,
		4, true,
		3, true,
		rand_r(4,5), true,
		//min 16 max 19
	},
};

void game_init()
{

	bobj_init();
	juge_init();
	vase_init();
	book_init();
	cloud_init();
	snowman_init();
	enemy_init();

	game_state = 0;
	game_timer = 0;

	for (int i = 0; i < 7; i++) {
		safe_delete(main_data[i].spr);
	}

	for (int i = 0; i < 7; i++) {
		safe_delete(under_data[i].spr);
	}
}

void game_deinit()
{
	fairy_deinit();
	bobj_deinit();
	juge_deinit();
	vase_deinit();
	book_deinit();
	cloud_deinit();
	snowman_deinit();
	enemy_deinit();

	music::stop(BGM_GAME);

	//safe_delete(spr_BACK);
	//safe_delete(spr_BACKCLOUD);
	safe_delete(spr_CURSOR);
	safe_delete(spr_start);
	safe_delete(spr_H_CURSOR);
	safe_delete(spr_snowing);
	//safe_delete(spr_BACK_UNDER);

	for (int i = 0; i < 7; i++) {
		safe_delete(main_data[i].spr);
	}

	for (int i = 0; i < 7; i++) {
		safe_delete(under_data[i].spr);
	}

}

void game_update()
{

	switch (game_state) {

	case 0:
		//spr_BACK = sprite_load(L"./Data/Images/MAIN_back.png");
		//spr_BACKCLOUD = sprite_load(L"./Data/Images/backKUMO.png");
		//spr_BACK_UNDER = sprite_load(L"./Data/Images/backKUMO_under.png");
		
		//BACK[] = {};

		for (int i = 0; i < 7; i++) {
			main_data[i].spr = sprite_load(main_data[i].filepath);
		}

		for (int i = 0; i < 7; i++) {
			under_data[i].spr = sprite_load(under_data[i].filepath);
		}


		spr_snowing = sprite_load(L"./Data/Images/snowing.png");


		spr_CURSOR = sprite_load(L"./Data/Images/cursor_anime.png");
		spr_start = sprite_load(L"./Data/Images/start.png");
		spr_H_CURSOR = sprite_load(L"./Data/Images/hammer_anime.png");

		fairy_init();

		++game_state;

	case 1:
		
		//snowing_posY = 550;
		snowing_speed = 0.1f;
		
		if (STAGE_NUM > 0) {
			music::stop(BGM_TITLE);
			music::play(BGM_GAME);
			music::setVolume(BGM_GAME, 0.2f);
		}

		cursor_posX = SCREEN_W/2;
		cursor_posY = SCREEN_H/2;

		GameLib::setBlendMode(Blender::BS_ALPHA);
		++game_state;

	case 2: 
		fairy_update();
		bobj_update();
		juge_update();
		book_update();
		snowman_update();


		//if (Fairy_flag >= 7) {
			enemy_update();
		//}

		if (vase_update(set_diff[STAGE_NUM]) == SCENE_SCORE)
		{
			nextScene = SCENE_SCORE;
			break;
		}


		if (cloud_update()|| (snowman_update() && STAGE_NUM > 0) )
		{
			for (int j = 0; j < ENEMY_MAX; j++) {
				Enemyflagdie(&Enemy[j]);
			}

			nextScene = SCENE_GAME_OVER;
			break;
		}

		game_Mmove();  //マウスの処理


		if (TRG(0)& PAD_START) {
			Fairy_flag += 1;
		}


		//cursorのアニメ
		if (game_timer % 4 == 0) {
			cursor_timer_g++;
			if (cursor_timer_g > 7) {
				cursor_timer_g = 0;
			}

		}
		cursor_texPosX_g = cursor_timer_g * 35;


		if (game_timer % 6 == 0) {
			hammer_timer++;
			if (hammer_timer > 2) {
				hammer_timer = 0;
			}

		}

		hammer_texPosX = hammer_timer * 45;

		snowing_posY += snowing_speed;
	
		break;
		
	}
	++game_timer;
}

void game_render()
{
	sprite_render(
		main_data[STAGE_NUM].spr,
		0, 0
	);

	sprite_render(
		spr_snowing,
		0, snowing_posY,
		1, 1,
		0, 0,
		1500, 1400
	);

	sprite_render(
		under_data[STAGE_NUM].spr,
		0, 0
	);



	cloud_render();
	book_render();
	snowman_render();
	if (STAGE_NUM == 0) {bobj_draw();}
	fairy_render();
	if (STAGE_NUM > 0) {bobj_draw();}
	vase_draw();
	juge_draw();
	enemy_render();



	//stage0(テュートリアル)にが出ないように
	if (STAGE_NUM > 0) {
		if (game_timer < 60) {
			sprite_render(
				spr_start,
				0, 0
			);
		}
	}


	//マウスのレンダ
	if (R_mouse() == false) {
		sprite_render(
			spr_CURSOR,
			cursor_posX, cursor_posY,
			1, 1,
			cursor_texPosX_g, 0,
			35, 55,
			0, 0,
			100
		);
	}

	if (R_mouse() == true) {

		sprite_render(
			spr_H_CURSOR,
			cursor_posX, cursor_posY,
			1, 1,
			hammer_texPosX, 0,
			45, 45,
			0, 0,
			0
		);


	}
	
}

void game_Mmove()
{
	//cursorの移動

//if (STATE(0) & PAD_RIGHT) {cursor_posX += 5;}
//if (STATE(0) & PAD_LEFT) { cursor_posX -= 5; }
//if (STATE(0) & PAD_UP) { cursor_posY -= 5; }
//if (STATE(0) & PAD_DOWN) { cursor_posY += 5; }

    ShowCursor(FALSE);
	GetCursorPos(&po);
	ScreenToClient(window::getHwnd(), &po);
	cursor_posX = po.x;
	cursor_posY = po.y;
	if (cursor_posX >= SCREEN_W - 37) { cursor_posX = SCREEN_W - 37; }
	if (cursor_posX <= 0) { cursor_posX = 0; }
	if (cursor_posY <= 0) { cursor_posY = 0; }
	if (cursor_posY >= SCREEN_H - 53) { cursor_posY = SCREEN_H - 53; }
}


VECTOR2 GetCposition()
{
	return { cursor_posX, cursor_posY };
}


bool R_mouse() {
	if (GetAsyncKeyState(MK_RBUTTON)) { return true; }
}

int rand_r(int min, int max) {
	int r = 0;
	srand((unsigned)time(NULL));
	r = rand() % (max + 1 - min) + min;
	return r;
}