#include "SunBullet.h"

extern Atlas atlas_sun;
extern Atlas atlas_sun_explode;
extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;
extern Atlas atlas_sun_text;


SunBullet::SunBullet()
{

	animation_sun[0].set_atlas(&atlas_sun);
	animation_sun[1].set_atlas(&atlas_sun_explode);
	animation_sun[0].set_interval(100);
	animation_sun[1].set_interval(100);
	animation_sun[0].set_loop(true);
	animation_sun[1].set_loop(false);

	pos = { -100,-100 };

	size.x = animation_sun[0].get_atlas()->get_image(0)->getwidth();
	size.y = animation_sun[0].get_atlas()->get_image(0)->getheight();

	size_explode.x = animation_sun[1].get_atlas()->get_image(0)->getwidth();
	size_explode.y = animation_sun[1].get_atlas()->get_image(0)->getheight();

	damage = 20;
	energy = 20;

	speed = { 0.5,-0.5 };//³õÊ¼ÎªÐ±Å×
	a = 0.001;
}

SunBullet::~SunBullet()
{
}

bool SunBullet::check_collide(Point pos, Rect rect)
{
	const bool is_coll= Bullet::check_collide(pos, rect);
	if (is_coll) {
		is_valid = false;
		//std::cout << "music" << std::endl;
		mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);

		scene_manager.getCmaera().setJitter_TimeAndR(400, 1);
		scene_manager.getCmaera().setJitterStart(true);
		scene_manager.getCmaera().getTimer().set_one_shot(true);
		scene_manager.getCmaera().getTimer().set_wait_time(scene_manager.getCmaera().getJitterTime());
		scene_manager.getCmaera().getTimer().restart();
	}
	if (!is_valid) {

	}
	return is_coll;
}

bool SunBullet::check_collide(Rect rect1, Rect rect2)
{
	const bool is_coll= Bullet::check_collide(rect1, rect2);
	return is_coll;
}

void SunBullet::on_update(int delta_time)
{
	if (is_valid) {
		speed.y += a * delta_time;

		pos.x += speed.x * delta_time;
		pos.y += speed.y*delta_time;
		if (!is_remove)
			animation_sun[0].on_update(delta_time);
	}
	else if (!is_valid) {
		if (!is_remove)
			animation_sun[1].on_update(delta_time);
		if (animation_sun[1].isend()) {
			is_remove = true;
			animation_sun[1].reset();
		}
	}
}

void SunBullet::on_draw(const Camera& camera)
{
	if (is_valid) {
		Bullet::on_draw(camera);
		animation_sun[0].on_draw(camera, pos.x, pos.y);
	}
	else if (!is_valid) {
		const Point mid = { pos.x - size_explode.x / 2 + size.x / 2, pos.y - size_explode.y / 2 + size.y / 2 };
		animation_sun[1].on_draw(camera, mid.x,mid.y);
		if (is_debug) {
			drawRect(camera, mid, { mid.x + size_explode.x, mid.y + size_explode.y });
		}
	}
}
