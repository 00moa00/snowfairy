#include "all.h"


int enemy_state;
int enemy_timer;

float enemy_moveX, enemy_moveY;
const float enemy_speed_max = 1.0f;

extern int STAGE_NUM, Fairy_flag;

OBJ2D Enemy[ENEMY_MAX];

struct ENEMY_DATA
{
	Sprite* spr;
	const wchar_t* filepath;      //画像用ファイルパス
	int atack;                    //攻撃力
	int defence;                  //防御力
	VECTOR2         texPos;
	VECTOR2         texSize;
	VECTOR2         pivot;
	int diff;                     //オブジェクトの種類
	OBJ2D::FUNC_PTR movealg;       //オブジェクトの動作(関数ポインタ)
	
};

ENEMY_DATA enemy_data[] =
{ {NULL, L"./Data/Images/Enemy/enemy_balloon.png", 25, 0, {0.0f, 0.0f}, {100.0f, 150.0f}, {0.0f, 0.0f}, BALLOON, move_Balloon},
  {NULL, L"./Data/Images/Enemy/enemy_raven.png", 40, 0, {0.0f, 0.0f}, {100.0f, 65.0f}, {0.0f, 0.0f}, BIRD, move_bird},
  {NULL, L"./Data/Images/Enemy/enemy_thief_anime.png", 250, 0, {0.0f, 0.0f}, {100.0f, 90.0f}, {0.0f, 0.0f}, FLIGHT, move_thief}

};

//struct ENEMY_SET
//{
//	int         stage;
//	int         enemyType;
//	VECTOR2     pos;
//} enemySet[] = {
//	{  0,  0, {  rand() % SCREEN_W, SCREEN_H } },
//	{  0,  0, {  rand() % SCREEN_W, SCREEN_H } },
//	{  0,  0, {  rand() % SCREEN_W, SCREEN_H } },
//	{  0,  1, { SCREEN_W + 150, 600.0f } },
//	{  0,  1, { SCREEN_W + 150, 600.0f } },
//	{  0,  1, { SCREEN_W + 150, 600.0f } },
//	{  0,  1, { SCREEN_W + 150, 600.0f } },
//	{  0,  1, { SCREEN_W + 150, 600.0f } },
//	{ -1, -1, {   -1,  -1 } },
//};

void enemy_init() {
    enemy_state = 0;
    enemy_timer = 0;
}
void enemy_deinit(){

	int datanum = sizeof(enemy_data) / sizeof(ENEMY_DATA);
	for(int i= 0; i<datanum; i++)
	safe_delete(enemy_data[i].spr);
}
void enemy_update(){


	int datanum =  sizeof(enemy_data) / sizeof(ENEMY_DATA);
	int diff;   //enemyの種類を決める用変数

	switch (enemy_state)
	{
	case 0 :
		for (int i = 0; i < datanum; i++)
		{
			enemy_data[i].spr = sprite_load(enemy_data[i].filepath);
		}

		enemy_state++;
		/*fallthrough*/
	case 1 :
		    for (int i = 0; i < ENEMY_MAX; i++)
			Enemy[i] = {};
			

			enemy_moveX = (float)((rand() * enemy_speed_max) / RAND_MAX);
			enemy_moveY =  (float)((rand() * enemy_speed_max) / RAND_MAX) + 1.0f;

		    //ramdomで   出現位置とスピード  決める
			for (int i = 0; i < datanum; i++)
			{
				//Setenemy(Enemy, ENEMY_MAX, enemy_data[i].movealg, VECTOR2(rand() % SCREEN_W, SCREEN_H), VECTOR2(enemy_moveX, enemy_moveY), enemy_data[0].diff);
			}


		enemy_state++;
		/*fallthrough*/
	case 2 :
	    
		if (Fairy_flag >= 7) {

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				diff = 0; 

				if (Enemy[i].moveAlg == nullptr)
				{
					diff = rand() % datanum;

					if (rand() % 100 == 0)	//Setenemy(Enemy, ENEMY_MAX, enemy_data[diff].movealg, VECTOR2(rand() % SCREEN_W, SCREEN_H), VECTOR2(enemy_moveX, enemy_moveY), enemy_data[diff].diff);
					////ステージごとに敵の出現
					{
						//diff = rand() % datanum;
						if (STAGE_NUM < 3) {
							Setenemy(Enemy, ENEMY_MAX, enemy_data[0].movealg, VECTOR2(rand() % SCREEN_W, SCREEN_H), VECTOR2(enemy_moveX, enemy_moveY), enemy_data[0].diff);
						}
						else if (STAGE_NUM < 5)
						{
								if (diff == 2) continue;
								Setenemy(Enemy, ENEMY_MAX, enemy_data[diff].movealg, VECTOR2(rand() % SCREEN_W, SCREEN_H), VECTOR2(enemy_moveX, enemy_moveY), enemy_data[diff].diff);

						}
						else if (STAGE_NUM < 7) {

							/*if (diff == FLIGHT)
							{
								if ((Enemy[0].diff == FLIGHT || Enemy[1].diff == FLIGHT || Enemy[2].diff == FLIGHT)) diff = 1;
							}*/

							Setenemy(Enemy, ENEMY_MAX, enemy_data[diff].movealg, VECTOR2((rand() % SCREEN_W - 50) + 50, SCREEN_H), VECTOR2(enemy_moveX, enemy_moveY), enemy_data[diff].diff);
						}
					}

					continue;
				}

				//Enemy[i].isflag = true;
				if (Enemy[i].moveAlg != nullptr)
				{
					(*Enemy[i].moveAlg)(&Enemy[i]);

					Enemy[i].timer++;
				}

			}
		}
		break;
	}

	enemy_timer++;
}
void enemy_render() {

	//Enemy[i].isflag==true付けたらなくなる時のアニメが出ないので(111行)一旦コメントしました
	//雲の描画
	for (int i = 0; i < ENEMY_MAX-1; i++)
	{
	if (Enemy[i].moveAlg) {
		sprite_render(Enemy[i].data,
			Enemy[i].pos.x, Enemy[i].pos.y,
			Enemy[i].scale.x, Enemy[i].scale.y,
			Enemy[i].texPos.x, Enemy[i].texPos.y,
			Enemy[i].texSize.x, Enemy[i].texSize.y,
			Enemy[i].pivot.x, Enemy[i].pivot.y);

		//primitive::rect(Enemy[i].pos.x , Enemy[i].pos.y, Enemy[i].texSize.x /, Enemy[i].texSize.y, 0, 0);

		 }
	}

}

void move_Balloon(OBJ2D* enemy)
{
	//debug::setString("detayo");
	switch (enemy->state)
	{
	case 0:
		enemy->scale = { 1.0f, 1.0f };
		enemy->color = { 1, 1, 1, 1 };
		enemy->atacck = enemy_data[0].atack;
		enemy->defence = enemy_data[0].defence;
		enemy->data = enemy_data[0].spr;
		enemy->texPos = enemy_data[0].texPos;
		enemy->texSize = enemy_data[0].texSize;
		enemy->pivot = enemy_data[0].pivot;
		enemy->hp = 10;

		enemy->state++;
		/*fallthrough*/

	case 1:

		if (enemy->timer % 120 == 0)
		{
			if (rand() % 2 == 0)  enemy->speed.x = -enemy->speed.x;   //ランダムで生成された数値が偶数ならx軸方向のスピードの向きを変える
		}

		enemy->pos.x += enemy->speed.x;
		enemy->pos.y -= enemy->speed.y;

		if (enemy->pos.y < MCLOUD_POSY + 115) {
			enemy->pos.y = MCLOUD_POSY + 115;
			enemy->speed = {0.0f, 0.0f};
		}
		//Enemy->pos.x = std::min(Enemy->pos.x, SCREEN_W - 50.0f);  //x軸に関する移動制限
		//Enemy->pos.x = std::max(Enemy->pos.x, 0.0f + 50.0f);      //y軸に関する移動制限

		if (enemy->pos.x > SCREEN_W - 50.0f) enemy->isflag = false;
		if (enemy->pos.x < 0.0f + 50.0f) enemy->isflag = false;

		if (!enemy->isflag) Enemy_anime_ballon(enemy, 4);

		break;

	}

}

void move_bird(OBJ2D* enemy)
{
	//if (enemy_data[1].diff) {
	//	debug::setString("hidari");
		switch (enemy->state)
		{
		case bird_init:  //初期化
			enemy->pos = { SCREEN_W + 150, 600.0f };
			enemy->speed = { 2.0f, 1.0f };
			enemy->scale = { 1.0f, 1.0f };
			enemy->color = { 1, 1, 1, 1 };
			enemy->atacck = enemy_data[1].atack;
			enemy->defence = enemy_data[1].defence;
			enemy->data = enemy_data[1].spr;
			enemy->texPos = enemy_data[1].texPos;
			enemy->texSize = enemy_data[1].texSize;
			enemy->pivot = enemy_data[1].pivot;
			enemy->hp = 10;

			enemy->state = bird_moveL_init;
			/*fallthrough*/

		case bird_moveL_init:  //左移動_初期

			enemy->scale = { 1.0f, 1.0f };
			enemy->anime = 0;
			enemy->animeTimer = 0;
			enemy->texPos = { 0.0f, 0.0f };
			enemy->state++;
			/*fallthrough*/
		case bird_moveL:  //左移動

			enemy->pos.x -= enemy->speed.x;

			enemy->timer++;

			if (rand() % 300 == 0 && enemy->pos.x < SCREEN_W - 200.0f)
			{
				enemy->state = bird_atc_init;
			}

			if (0.0f + 150.0f > enemy->pos.x)
			{
				enemy->state = bird_moveR_init;
			}

			break;


		case bird_moveR_init:  //右移動_初期
			enemy->scale = { -1.0f, 1.0f };
			enemy->anime = 0;
			enemy->animeTimer = 0;
			enemy->texPos = { 0.0f, 0.0f };
			enemy->state++;
			/*fallthrough*/

		case bird_moveR:  //右移動
			enemy->pos.x += enemy->speed.x;

			if (SCREEN_W - 250.0f < enemy->pos.x)
			{
				enemy->state = bird_moveL_init;
			}

			break;

		case bird_atc_init:  //攻撃準備移動_初期
			(enemy->pos.x > SCREEN_W / 2.0f) ? enemy->scale = { 1.0f, 1.0f } : enemy->scale = { -1.0f, 1.0f };
			enemy->timer = 0;
			enemy->Aflag = false;
			enemy->anime = 0;
			enemy->animeTimer = 0;
			enemy->texPos = { 0.0f, 0.0f };
			enemy->state++;
			/*fallthrough*/

		case bird_atc:  //攻撃準備移動
			enemy->pos.y -= enemy->speed.y;

			if (enemy->pos.y <= MCLOUD_POSY + 115)
			{
				enemy->pos.y = MCLOUD_POSY + 115;
				enemy->state = bird_atc_Ainit;
			}

			break;

		case bird_atc_Ainit:
			enemy->timer = 0;
			enemy->anime = 0;
			enemy->animeTimer = 0;
			enemy->texPos = { 0.0f, 0.0f };
			enemy->state++;
			/*fallthrough*/

		case bird_atc_A:    //攻撃のアニメーション
			if (enemy->timer == 500) enemy->Aflag = true;


			if (enemy->timer >= 1000) enemy->state = bird_atcr_init;
			break;

		case bird_atcr_init:
			enemy->anime = 0;
			enemy->animeTimer = 0;
			enemy->texPos = { 0.0f, 0.0f };
			enemy->state++;
			/*fallthrough*/

		case bird_atcr:
			enemy->pos.y += enemy->speed.y;
			if (enemy->pos.y >= 600.0f)
			{
				(enemy->pos.x > SCREEN_W / 2.0f) ? enemy->state = bird_moveL_init : enemy->state = bird_moveR_init;
			}
			break;

		case bird_diemove_init:
			enemy->anime = 0;
			enemy->animeTimer = 0;
			enemy->texPos = { 0.0f, 65.0f };
			enemy->state++;
			/*fallthrough*/

		case bird_diemove:
			enemy->pos.y += enemy->speed.y;
			if (enemy->pos.y > SCREEN_H + 65.0f)
			{
				enemy->moveAlg = nullptr;
				enemy = nullptr;
			}
			break;

		}


		if (!enemy->isflag)
		{
			Enemy_anime_diebird(enemy, 8);
			//Enemy_anime_bird(enemy, 8);
			if (enemy->state != bird_diemove)
				enemy->state = bird_diemove_init;
		}
		else Enemy_anime_bird(enemy, 8);

		enemy->timer++;
	//}
}

void move_thief(OBJ2D* enemy)
{

	switch (enemy->state)
	{
	case thief_init:
		(rand() % 2 == 0) ?
		enemy->pos = { SCREEN_W + 150, 400.0f } : enemy->pos = { 0 - 150, 400.0f };
		enemy->speed = { 0.6f, 0.0f };
		enemy->scale = { 1.0f, 1.0f };
		enemy->color = { 1, 1, 1, 1 };
		enemy->atacck = enemy_data[2].atack;
		enemy->defence = enemy_data[2].defence;
		enemy->data = enemy_data[2].spr;
		enemy->texPos = enemy_data[2].texPos;
		enemy->texSize = enemy_data[2].texSize;
		enemy->pivot = enemy_data[2].pivot;
		enemy->hp = 10;

		(enemy->pos.x < SCREEN_W / 2) ?
		enemy->state = thief_moveR_init : enemy->state = thief_moveL_init;

		break;
		//enemy->state++;
		/*fallthrough*/

	case thief_moveL_init:  //左移動_初期

		enemy->scale = { -enemy->scale.x, 1.0f };
		enemy->anime = 0;
		enemy->animeTimer = 0;
		enemy->texPos = { 0.0f, 0.0f };
		enemy->state++;
		/*fallthrough*/

	case thief_moveL:
		enemy->pos -= enemy->speed;
		break;

	case thief_moveR_init:  //右移動_初期
		enemy->scale = { 1.0f, 1.0f };
		enemy->anime = 0;
		enemy->animeTimer = 0;
		enemy->texPos = { 0.0f, 0.0f };
		enemy->state++;
		/*fallthrough*/

	case thief_moveR:  //右移動
		enemy->pos += enemy->speed;


		break;

	case thief_diemove_init:
		(enemy->pos.x < SCREEN_W / 2) ?
			enemy->state = thief_diemoveR_init : enemy->state = thief_diemoveL_init;
		enemy->anime = 0;
		enemy->animeTimer = 0;
		enemy->texPos.y = 90.0f;
		break;
	case thief_diemoveL_init:
		enemy->scale = { 1.0f, 1.0f };
		enemy->state++;
		/*fallthrough*/
	case thief_diemoveL:
		enemy->pos += enemy->speed;
		if (enemy->pos.x > SCREEN_W + 150) enemy->moveAlg = nullptr;
		break;
	case thief_diemoveR_init:
		enemy->scale = { -1.0f, 1.0f };
		enemy->state++;
		/*fallthrough*/
	case thief_diemoveR:
		enemy->pos -= enemy->speed;
		if (enemy->pos.x < 0 - 150) enemy->moveAlg = nullptr;
		break;


	}
	if (!enemy->isflag)
	{
		Enemy_anime_diethief(enemy, 4);
		if(enemy->state != thief_diemoveL && enemy->state != thief_diemoveR && enemy->state != thief_diemoveL_init && enemy->state != thief_diemoveR_init)
		enemy->state = thief_diemove_init;

	}
	else Enemy_anime_thief(enemy, 4);
		//debug::setString("dorobou");

}


void Enemyflagdie(OBJ2D* obj)
{

	obj->isflag = false;                     //isflagをfalseにする
	//obj->moveAlg = nullptr;
	//obj->timer = 0;

}

void Enemy_damage(OBJ2D* obj, int a)
{
	obj->hp -= a;
}

bool Enemy_ischeck(OBJ2D* obj)  //HPが0になるとtrueを返す
{
	if (obj->hp <= 0) return true;

	return false;
}

void Enemy_anime_ballon(OBJ2D* obj, int koma)
{
	//animeTimerとanimeはOBH2D::setenemyの関数内ですべての変数がクリアされるので消える度にリセットされる
	if ((obj->animeTimer) % koma == 0) {

		obj->anime++;

		if (obj->anime > 8) {
			obj->moveAlg = nullptr;
		}
	}
	obj->texPos.x = obj->anime * obj->texSize.x;
	obj->animeTimer++;
}

void Enemy_anime_bird(OBJ2D* obj, int koma)
{
	//animeTimerとanimeはOBH2D::setenemyの関数内ですべての変数がクリアされるので消える度にリセットされる


	if ((obj->animeTimer) % koma == 0) {

		obj->anime++;

		if (obj->anime > 2) {
			obj->anime = 0;
		}
	}
	obj->texPos.x = obj->anime * obj->texSize.x;
	obj->animeTimer++;
}


void Enemy_anime_diebird(OBJ2D* obj, int koma)
{
	//animeTimerとanimeはOBH2D::setenemyの関数内ですべての変数がクリアされるので消える度にリセットされる
	if ((obj->animeTimer) % koma == 0) {

		obj->anime++;

		if (obj->anime > 8) {
			obj->anime = 0;
			obj->moveAlg = nullptr;
		}
	}
	obj->texPos.x = obj->anime * obj->texSize.x;
	obj->animeTimer++;
}

void Enemy_anime_thief(OBJ2D* obj, int koma)
{
	if ((obj->animeTimer) % koma == 0) {

		obj->anime++;

		if (obj->anime > 11) {
			obj->anime = 0;
		}
	}
	obj->texPos.x = obj->anime * obj->texSize.x;
	obj->animeTimer++;
}

void Enemy_anime_diethief(OBJ2D* obj, int koma)
{
	if ((obj->animeTimer) % koma == 0) {

		obj->anime++;

		if (obj->anime > 11) {
			obj->anime = 0;
			//obj->moveAlg = nullptr;
		}
	}
	obj->texPos.x = obj->anime * obj->texSize.x;
	obj->animeTimer++;
}
