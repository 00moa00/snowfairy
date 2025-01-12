#include "all.h"


int gameOver_state;
int gameOver_timer;

int cursor_texPosX_o;
int cursor_timer_o;

float cursor_posX_o;
float cursor_posY_o;


Sprite* spr_GAMEOVER;
Sprite* spr_CURSOR_O;

POINT pov;


void gameOver_init()
{

	gameOver_state = 0;
	gameOver_timer = 0;
	music::play(BGM_GAMEOVER);

}

void gameOver_deinit()
{
	safe_delete(spr_CURSOR_O);
}

void gameOver_update()
{

	switch (gameOver_state) {

	case 0:

		spr_GAMEOVER = sprite_load(L"./Data/Images/game_over.png");
		spr_CURSOR_O = sprite_load(L"./Data/Images/cursor_anime.png");

		++gameOver_state;

	case 1:
		cursor_posX_o = SCREEN_W / 2;
		cursor_posY_o = SCREEN_H / 2;

		GameLib::setBlendMode(Blender::BS_ALPHA);
		++gameOver_state;

	case 2:

		if (TRG(0) & PAD_START)
		{

			nextScene = SCENE_TITLE;
			break;
		}

		ShowCursor(FALSE);
		GetCursorPos(&pov);
		ScreenToClient(window::getHwnd(), &pov);
		cursor_posX_o = pov.x;
		cursor_posY_o = pov.y;

		if (cursor_posX_o >= SCREEN_W - 37) { cursor_posX_o = SCREEN_W - 37; }
		if (cursor_posX_o <= 0) { cursor_posX_o = 0; }
		if (cursor_posY_o <= 0) { cursor_posY_o = 0; }
		if (cursor_posY_o >= SCREEN_H - 53) { cursor_posY_o = SCREEN_H - 53; }

		//cursor‚ÌƒAƒjƒ
		if (gameOver_timer % 4 == 0) {
			cursor_timer_o++;
			if (cursor_timer_o > 7) {
				cursor_timer_o = 0;
			}
		}
		cursor_texPosX_o = cursor_timer_o * 35;

		break;
	}

	//debug::setString("title_timer:%d", gameOver_timer);
	++gameOver_timer;

}

void gameOver_render()
{
	GameLib::clear(0.2f, 0.2f, 0.3f);
	sprite_render(spr_GAMEOVER, 0, 0);

	sprite_render(
		spr_CURSOR_O ,
		cursor_posX_o, cursor_posY_o,
		1, 1,
		cursor_texPosX_o, 0,
		35, 55,
		0, 0,
		100
	);


}