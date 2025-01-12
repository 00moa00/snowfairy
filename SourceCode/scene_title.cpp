#include "all.h"


int title_state;
int title_timer;

extern int STAGE_NUM;
extern int Fairy_flag;
Sprite* spr_Title;
Sprite* spr_TI_CURSOR;

float cursor_posX_ti, cursor_posY_ti;
POINT pt;

int cursor_texPosX;
int cursor_timer;



void title_init()
{

	title_state = 0;
	title_timer = 0;  

}

void title_deinit()
{
	safe_delete(spr_Title);
	safe_delete(spr_TI_CURSOR);
	
}

void title_update()
{

	switch (title_state) {
		
	case 0: 
		
		//sprTitle = sprite_load(L"./Data/Images/logo.png");
		spr_Title = sprite_load(L"./Data/Images/title.png");
		spr_TI_CURSOR = sprite_load(L"./Data/Images/cursor_anime.png"); //35

		++title_state;
		
	case 1 :
		

		cursor_posX_ti = SCREEN_W / 3;
		cursor_posY_ti = SCREEN_H / 3;

		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(BGM_TITLE);
		music::setVolume(BGM_TITLE, 0.2f);

		GameLib::setBlendMode(Blender::BS_ALPHA);
		++title_state;

	case 2 :



		if (GetAsyncKeyState(MK_LBUTTON)) {

			//720~1200 , 320~450
			//テュートリアル
			if (cursor_posX_ti > 455 && cursor_posX_ti < 825 && cursor_posY_ti>335 && cursor_posY_ti < 433) {
				Fairy_flag = 0;
				STAGE_NUM = 0;
				nextScene = SCENE_GAME;
				break;
			}
			if (cursor_posX_ti > 455 && cursor_posX_ti < 825 && cursor_posY_ti>460 && cursor_posY_ti < 560) {
				STAGE_NUM = 1;

				Fairy_flag = FAIRY_SERIHU_MAX ;
				nextScene = SCENE_GAME;
				break;
			}

			if (cursor_posX_ti > 455 && cursor_posX_ti < 825 && cursor_posY_ti>585 && cursor_posY_ti < 685) {
				//return 0;
				//終了フラグ....
				PostQuitMessage(0);  //終了処理を行う関数
			}
		}
		ShowCursor(FALSE);
		GetCursorPos(&pt);
		ScreenToClient(window::getHwnd(), &pt);
		cursor_posX_ti = pt.x;
		cursor_posY_ti = pt.y;

		if (cursor_posX_ti >= SCREEN_W - 37) { cursor_posX_ti = SCREEN_W - 37; }
		if (cursor_posX_ti <= 0) { cursor_posX_ti = 0; }
		if (cursor_posY_ti <= 0) { cursor_posY_ti = 0; }
		if (cursor_posY_ti >= SCREEN_H - 53) { cursor_posY_ti = SCREEN_H - 53; }


		if (title_timer % 4 == 0) {
			cursor_timer++;
			if (cursor_timer > 7) {
				cursor_timer = 0;
			}
		}
		cursor_texPosX = cursor_timer * 35;

		break;
	}

	//debug::setString("title_timer:%d", title_timer);
	++title_timer;

}

void title_render()
{
	//GameLib::clear(0.2f, 0.2f, 0.3f);

	sprite_render(spr_Title, 0, 0);

	sprite_render(
		spr_TI_CURSOR,
		cursor_posX_ti, cursor_posY_ti,
		1, 1,
		cursor_texPosX, 0,
		35, 55,
		0, 0,
		100
	);


}
