#include "all.h"

#define BOOK_POSY (((SCREEN_H/2)+50)-120)
#define BOOK_POSX ((SCREEN_W/2)-420)

int book_state, book_timer;

int book_p;

//表記判定用の変数参照
extern bool vase_daiya_c, vase_hosi_c, vase_heart_c, vase_spaed_c, vase_clober_c;
extern int vase_daiya, vase_hosi, vase_heart, vase_spaed, vase_clober;
extern int STAGE_NUM;


float book_posY;
float book_speed;

Sprite* sprBook;
Sprite* spr_ho;
Sprite* spr_he;
Sprite* spr_di;
Sprite* spr_cl;
Sprite* spr_sp;
Sprite* spr_num[10];

void book_init()
{
    book_state = 0;
	book_timer = 0;
}

void book_deinit()
{
	safe_delete(sprBook);
	safe_delete(spr_ho);
	safe_delete(spr_he);
	safe_delete(spr_di);
	safe_delete(spr_cl);
	safe_delete(spr_sp);
	for (int i = 0; i < 10; i++)
	{
		safe_delete(spr_num[i]);
	}
}

void book_update()
{
	switch (book_state)
	{
	case 0:
		sprBook = sprite_load(L"./Data/Images/Book/book.png");
		spr_ho = sprite_load(L"./Data/Images/Book/book_star.png");
		spr_he = sprite_load(L"./Data/Images/Book/book_heart.png");
		spr_di = sprite_load(L"./Data/Images/Book/book_diamond.png");
		spr_cl = sprite_load(L"./Data/Images/Book/book_club.png");
		spr_sp = sprite_load(L"./Data/Images/Book/book_spade.png");
		spr_num[0] = sprite_load(L"./Data/Images/Book/book0.png");
		spr_num[1] = sprite_load(L"./Data/Images/Book/book1.png");
		spr_num[2] = sprite_load(L"./Data/Images/Book/book2.png");
		spr_num[3] = sprite_load(L"./Data/Images/Book/book3.png");
		spr_num[4] = sprite_load(L"./Data/Images/Book/book4.png");
		spr_num[5] = sprite_load(L"./Data/Images/Book/book5.png");
		spr_num[6] = sprite_load(L"./Data/Images/Book/book6.png");
		spr_num[7] = sprite_load(L"./Data/Images/Book/book7.png");
		spr_num[8] = sprite_load(L"./Data/Images/Book/book8.png");
		spr_num[9] = sprite_load(L"./Data/Images/Book/book9.png");

		++book_state;

	case 1:
		if (STAGE_NUM <= 2) {book_p = 20;}
		if (STAGE_NUM >= 3) { book_p = 0; }

		book_posY = BOOK_POSY;
		book_speed = 0.05f;

		GameLib::setBlendMode(Blender::BS_ALPHA);
		++book_state;

	case 2:

		book_posY += book_speed;

		if (book_posY >= (BOOK_POSY + 2))
		{
			book_speed *= -1;
		}

		if (book_posY <= BOOK_POSY)
		{
			book_speed *= -1;
		}


		if (vase_daiya_c == false) {

		}

		break;
	}
	//++book_state;
}

void book_render() {
	//レシピ本の表示
	sprite_render(
		sprBook,
		BOOK_POSX, book_posY,
		1.0f, 1.0f,
		0, 0,
		260, 219
	);
	//星マークの表示
	if (vase_hosi_c)
	{
		sprite_render(
			spr_ho,
			BOOK_POSX + 150, book_posY+(37+book_p), 
			1, 1,
			0, 0,
			90, 20
		);
		//数字の表示
		sprite_render(
			spr_num[vase_hosi],
			BOOK_POSX + 165, book_posY+(37 + book_p),
			1, 1,
			0, 0,
			90, 20
		);

	}
	//ダイヤの表示
	//if (vase_daiya_c)
	//{
		sprite_render(
			spr_di,
			BOOK_POSX + 150, book_posY + (57 + book_p),
			1, 1,
			0, 0,
			90, 20
		);
		//数字の表示
		sprite_render(
			spr_num[vase_daiya],
			BOOK_POSX + 165, book_posY + (57 + book_p),
			1, 1,
			0, 0,
			90, 20
		);

	//}
	//ハートの表示
	if (vase_heart_c)
	{
		sprite_render(
			spr_he,
			BOOK_POSX + 150, book_posY + (77 + book_p),
			1, 1,
			0, 0,
			90, 20
		);
		//数字の表示
		sprite_render(
			spr_num[vase_heart],
			BOOK_POSX + 165, book_posY + (77 + book_p),
			1, 1,
			0, 0,
			90, 20
		);

	}
	//スペードの表示
	if (vase_spaed_c)
	{
		sprite_render(
			spr_sp,
			BOOK_POSX + 150, book_posY + 97,
			1, 1,
			0, 0,
			90, 20
		);
		//数字の表示
		sprite_render(
			spr_num[vase_spaed],
			BOOK_POSX + 165, book_posY + 97,
			1, 1,
			0, 0,
			90, 20
		);

	}
	//クローバーの表示
	if (vase_clober_c)
	{
		sprite_render(
			spr_cl,
			BOOK_POSX + 150, book_posY + 117,
			1, 1,
			0, 0,
			90, 20
		);
		//数字の表示
		sprite_render(
			spr_num[vase_clober],
			BOOK_POSX + 165, book_posY + 117,
			1, 1,
			0, 0,
			90, 20
		);

	}
}