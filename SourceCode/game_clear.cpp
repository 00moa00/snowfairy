#include "all.h"

//extern int STAGE_NUM;

int gameclear_state, gameclear_timer;


Sprite* spr_GAMECLEAR;


void gameclear_init()
{

	gameclear_state = 0;
	gameclear_timer = 0;
	//if (STAGE_NUM < 7) { music::play(BGM_GAMEOVER); }

}

void gameclear_deinit()
{
	safe_delete(spr_GAMECLEAR);
}

void gameclear_update()
{

	switch (gameclear_state) {

	case 0:

		spr_GAMECLEAR = sprite_load(L"./Data/Images/game_clear.png");

		++gameclear_state;

	case 1:
		

		GameLib::setBlendMode(Blender::BS_ALPHA);
		++gameclear_state;

	case 2:

		if (TRG(0) & PAD_START)
		{

			nextScene = SCENE_TITLE;
			break;
		}


		break;
	}

	++gameclear_timer;

}

void gameclear_render()
{
	sprite_render(spr_GAMECLEAR, 0, 0);


}