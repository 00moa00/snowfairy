#include "all.h"


int cloud_state, cloud_timer;

//float mcloud_posY;
float mcloud_speed;


int mcloud_HP; //‰_‚ÌHP
int damage;

extern int STAGE_NUM;

//Sprite* spr_MAINCLOUD;
OBJ2D Maincloud;

Sprite* spr_HPCLOUD;
Sprite* spr_HPBAR;
Sprite* spr_HPBASE;

void cloud_init() {

	cloud_state = 0;
	cloud_timer = 0;
}
void cloud_deinit() {
    safe_delete(Maincloud.data);
	safe_delete(spr_HPCLOUD);

}
bool cloud_update() {

	switch (cloud_state)
	{
	case 0:
		Maincloud.data = sprite_load(L"./Data/Images/mainKUMO.png");


		spr_HPCLOUD = sprite_load(L"./Data/Images/CLOUD_hp.png");
		spr_HPBAR = sprite_load(L"./Data/Images/HP_bar.png");
		spr_HPBASE = sprite_load(L"./Data/Images/HP_base.png");

	case 1:
		//maincloud
		mcloud_speed = 0.1f;

		Maincloud.pos = { 0, MCLOUD_POSY };
		Maincloud.scale = { 1.0f, 1.0f };
		Maincloud.texPos = {0,0};
		Maincloud.texSize = { 1280, 231 };
		Maincloud.pivot = { 0, 0 };



		//hp
		mcloud_HP = 250;
		//damage = 0;

		//damage‚ðŠÖ”‚©‚ç–á‚Á‚ÄÝ’è.

		GameLib::setBlendMode(Blender::BS_ALPHA);
		++cloud_state;

	case 2 :
		//main cloud‚ÌˆÚ“®
		Maincloud.pos.y += mcloud_speed;

		if (Maincloud.pos.y >= (MCLOUD_POSY + 8))
		{
			mcloud_speed *= -1;
		}

		if (Maincloud.pos.y <= MCLOUD_POSY)
		{
			mcloud_speed *= -1;
		}

	
	}

	//debug::setString("kumoHP:%d", mcloud_HP);

	if (mcloud_HP <= 0 && STAGE_NUM>0)
		return true;

	return false;

}
void cloud_render() {


	sprite_render(
	
		Maincloud.data,
		Maincloud.pos.x,	Maincloud.pos.y,
		Maincloud.scale.x,	Maincloud.scale.y,
		Maincloud.texPos.x, Maincloud.texPos.y,
		Maincloud.texSize.x,Maincloud.texSize.y,
		Maincloud.pivot.x,	Maincloud.pivot.y
	
	
	);

	sprite_render(
		spr_HPBASE,
		(SCREEN_W / 2)+2, (SCREEN_H)-38,
		1, 1,
		0, 0,
		250,40,
		124,20
	);

	sprite_render(
		spr_HPBAR,
		SCREEN_W / 2, (SCREEN_H)-38,
		1, 1,
		0, 0,
		mcloud_HP, 33,
		125, 20
	);

	sprite_render(
		spr_HPCLOUD,
		SCREEN_W/2, (SCREEN_H)-40,
		1,1,
		0,0,
		250,40,
		125,20
	);
}


void cloud_damek(int da)
{

	music::play(BGM_HIT);

	if(mcloud_HP > 0)
	mcloud_HP -= da;
}

void cloud_heal(int hp)
{
	if ((hp + mcloud_HP) > 250) {
		hp = 250 - mcloud_HP;
	}
	mcloud_HP += hp;
}