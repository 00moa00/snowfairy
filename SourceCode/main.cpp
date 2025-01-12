
#include "all.h"


int curScene  = SCENE_NONE;
int nextScene = SCENE_TITLE;



int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	GameLib::init(L"Snow Fairy", SCREEN_W, SCREEN_H);
	
	audio_init();

	while (GameLib::gameLoop())
	{
		
		if (curScene != nextScene) {

			switch (curScene)
			{
			case SCENE_TITLE:
				title_deinit();
				break;


			case SCENE_GAME:
				game_deinit();
				break;

			case SCENE_GAME_OVER:
				gameOver_deinit();
				break;

			case SCENE_SCORE:
				score_deinit();
				break;

			case SCENE_GAME_CLEAR:
				gameclear_deinit();
				break;

			}

			switch (nextScene)
			{
			case SCENE_TITLE:
				title_init();
				break;


			case SCENE_GAME:
				game_init();
				break;

			case SCENE_GAME_OVER:
				gameOver_init();
				break;

			case SCENE_SCORE:
				score_init();
				break;

			case SCENE_GAME_CLEAR:
				gameclear_init();
				break;
			}

			curScene = nextScene;
		}

		input::update();

		music::update();

		switch (curScene) {
		case SCENE_TITLE:
			title_update();
			title_render();
			break;


		case SCENE_GAME:
			game_update();
			game_render();
			break;

		case SCENE_GAME_OVER:
			gameOver_update();
			gameOver_render();
			break;

		case SCENE_SCORE:
			score_update();
			score_render();
			break;


		case SCENE_GAME_CLEAR:
			gameclear_update();
			gameclear_render();
			break;
		}

		debug::display(1, 0, 0,1,1);
		GameLib::present(1, 0);

	}

	switch (curScene)
	{
	case SCENE_TITLE:
		title_deinit();
		break;

	case SCENE_GAME:
		game_deinit();
		break;

	case SCENE_GAME_OVER:
		gameOver_deinit();
		break;

	case SCENE_SCORE:
		score_deinit();
		break;

	case SCENE_GAME_CLEAR:
		gameclear_deinit();
		break;


	}

	audio_deinit();

	GameLib::uninit();

	return 0; 
}