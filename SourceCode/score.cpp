#include "all.h"

int score_state, score_timer, score_hp, score_rank, score_stage;
extern int game_timer, mcloud_HP, STAGE_NUM, timer_texSizeX;

float cursor_posX_sc, cursor_posY_sc;

int cursor_texPosX_s;
int cursor_timer_s;

Sprite* spr_score;
Sprite* spr_SC_CURSOR;
OBJ2D Rank;

POINT pc;


struct SCORE_RANK {
	Sprite* spr;
	const wchar_t* filepath;
};

SCORE_RANK rank_data[]{
	{NULL, L"./Data/Images/Rank/C2.png"},
	{NULL, L"./Data/Images/Rank/B2.png"},
	{NULL, L"./Data/Images/Rank/A2.png"},
	{NULL, L"./Data/Images/Rank/S2.png"},
};


void score_init()
{
    score_state = 0;
    score_timer = 0;

	score_hp = 0;
	score_rank = 0;
	score_stage = 0;
	if(STAGE_NUM>1){
	music::play(BGM_CLEAR);
	}
}

void score_deinit()
{
	for (int i = 0; i < RANK_MAX; i++) {
		safe_delete(rank_data[i].spr);
	}
}

void score_update()
{

	
	switch(score_state)
	{
	case 0:

		//テュートリアルだけ終わったら出さないようにする
		//テュートリアル終わったらscene_score.cppには来ないようにしたかったけど、レシピの方でバッグ出る
		if (STAGE_NUM > 1) {spr_score = sprite_load(L"./Data/Images/stageclear.png");}

			spr_SC_CURSOR = sprite_load(L"./Data/Images/cursor_anime.png");

			for (int i = 0; i < RANK_MAX; i++) {
				rank_data[i].spr = sprite_load(rank_data[i].filepath);
			}
		++score_state;

	case 1:


		cursor_posX_sc = SCREEN_W / 2;
		cursor_posY_sc = SCREEN_H / 2;

		GameLib::setBlendMode(Blender::BS_ALPHA);
		++score_state;
	case 2:

		score_hp = mcloud_HP * 10;
		score_timer = timer_texSizeX * 10;
		score_stage = score_hp + score_timer;

		//ランク
		if (score_stage >= 1800) score_rank = 3;
		else if (score_stage >= 1300) score_rank = 2;
		else if (score_stage >= 1000) score_rank = 1;
		else if (score_stage >= 900) score_rank = 0;

		ShowCursor(FALSE);
		GetCursorPos(&pc);
		ScreenToClient(window::getHwnd(), &pc);
		cursor_posX_sc = pc.x;
		cursor_posY_sc = pc.y;

		if (cursor_posX_sc >= SCREEN_W - 37) { cursor_posX_sc = SCREEN_W - 37; }
		if (cursor_posX_sc <= 0) { cursor_posX_sc = 0; }
		if (cursor_posY_sc <= 0) { cursor_posY_sc = 0; }
		if (cursor_posY_sc >= SCREEN_H - 53) { cursor_posY_sc = SCREEN_H - 53; }


		if (STAGE_NUM == 1) {
			nextScene = SCENE_GAME;
			break;
		}
		else if ((TRG(0) & PAD_START) && STAGE_NUM < 6) {
			nextScene = SCENE_GAME;
			break;
		}


		if ((TRG(0) & PAD_START)&& STAGE_NUM == 6) {
			nextScene = SCENE_GAME_CLEAR;
			break;
		}

		//cursorのアニメ
		if (score_timer % 4 == 0) {
			cursor_timer_s++;
			if (cursor_timer_s > 7) {
				cursor_timer_s = 0;
			}
		}
		cursor_texPosX_s = cursor_timer_s * 35;

		break;
	}
	//debug::setString("map_timer:%d", score_timer);
	//debug::setString("stage_num:%d", STAGE_NUM);
	++score_timer;

}

void score_render()
{
	if (STAGE_NUM > 1) {
		sprite_render(
			spr_SC_CURSOR,
			cursor_posX_sc, cursor_posY_sc,
			cursor_texPosX_s, 1,
			1, 1,
			35, 55,
			0, 0,
			100
		);


		sprite_render(
			spr_score,
			0, 0
		);

	using namespace std;
	sprite_render(spr_score, 0, 0);
	ostringstream s_hp, s_timer, s_stage;

	s_hp << setw(6);
	s_hp << setfill('0');
	s_hp << score_hp;
	//
	s_timer << setw(6);
	s_timer << setfill('0');
	s_timer << score_timer;
	//
	s_stage << setw(6);
	s_stage << setfill('0');
	s_stage << score_stage;

	font::textOut(1,  s_hp.str() + "pt",
		{ 318, 183 },    //位置 
		{ 1, 1 },                          //サイズ
		{ 1.0f, 1.0f, 1.0f, 1 },   //色 R,G,B,透明度 
		TEXT_ALIGN::UPPER_LEFT);   //文字位置

	font::textOut(1,  s_timer.str() + "pt",
		{ 318, 255 },    //位置 
		{ 1, 1 },                          //サイズ
		{ 1.0f, 1.0f, 1.0f, 1 },    //色 R,G,B,透明度 
		TEXT_ALIGN::UPPER_LEFT);   //文字位置

	font::textOut(1,  s_stage.str() + "pt",
		{ 318, 344 },    //位置 
		{ 1, 1 },                          //サイズ
		{ 1.0f, 1.0f, 1.0f, 1 },    //色 R,G,B,透明度 
		TEXT_ALIGN::UPPER_LEFT);   //文字位置

	sprite_render(
		rank_data[score_rank].spr,
		191, 365
	);
		
	}

}
