#include "SunBulletEx.h"


extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;
extern Atlas atlas_sun_text;

extern bool is_debug;

SunBulletEx::SunBulletEx()
{
	animation_sun[0].set_atlas(&atlas_sun_ex);
	animation_sun[1].set_atlas(&atlas_sun_ex_explode);
	animation_sun[0].set_interval(50);
	animation_sun[1].set_interval(100);
	animation_sun[0].set_loop(true);
	animation_sun[1].set_loop(false);

	animation_sun_text.set_atlas(&atlas_sun_text);
	animation_sun_text.set_interval(100);
	animation_sun_text.set_loop(false,2);


	size.x = animation_sun[0].get_atlas()->get_image(0)->getwidth();
	size.y = animation_sun[0].get_atlas()->get_image(0)->getheight();

	size_explode.x = animation_sun[1].get_atlas()->get_image(0)->getwidth();
	size_explode.y = animation_sun[1].get_atlas()->get_image(0)->getheight();

	pos = { -100,-100 };

	damage = 50;
	energy = 80;

	speed = { 0,0.2 };//初始匀速

	a = 0;//加速度为零

}

SunBulletEx::~SunBulletEx()
{
}

bool SunBulletEx::check_collide(Point pos, Rect rect)
{
	return false;
}

bool SunBulletEx::check_collide(Rect rect1, Rect rect2)
{
	const bool is_coll = Bullet::check_collide(rect1, rect2);

	if (is_coll) {
		is_valid = false;

		std::cout << "music" << std::endl;
		mciSendString(_T("play sun_explode_ex from 0"), NULL, 0, NULL);

		scene_manager.getCmaera().setJitter_TimeAndR(400, 5);
		scene_manager.getCmaera().setJitterStart(true);
		scene_manager.getCmaera().getTimer().set_one_shot(true);
		scene_manager.getCmaera().getTimer().set_wait_time(scene_manager.getCmaera().getJitterTime());
		scene_manager.getCmaera().getTimer().restart();
	}
	//其他操作
	if (!is_valid) {

	}

	return is_coll;
}

void SunBulletEx::on_update(int delta_time)
{
	SunBullet::on_update(delta_time);
	
	if(is_exist_text)animation_sun_text.on_update(delta_time);
}

void SunBulletEx::on_draw(const Camera& camera)
{
	SunBullet::on_draw(camera);

	if (is_exist_text)animation_sun_text.on_draw(camera, text_pos.x, text_pos.y);
	if (animation_sun_text.isend())is_exist_text = false;

	if (!is_valid) {
		if (is_debug) {
			const Point mid = { pos.x - size_explode.x / 2 + size.x / 2, pos.y - size_explode.y / 2 + size.y / 2 };
			drawRect(camera, mid, { mid.x + size_explode.x, mid.y + size_explode.y });
		}
	}

}

void SunBulletEx::setTextPos(Point pos)
{
	text_pos.x = pos.x - 50;
	text_pos.y = pos.y;
}

void SunBulletEx::setTextExist(bool flag)
{
	is_exist_text = flag;
}

Animation& SunBulletEx::getAniamtionText()
{
	return animation_sun_text;
}
