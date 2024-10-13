#include "PeaBullet.h"
#include <iostream>

extern IMAGE img_pea;

extern Atlas atlas_pea_break;

PeaBullet::PeaBullet()
{
	img = &img_pea;

	animation.set_atlas(&atlas_pea_break);
	animation.set_interval(100);
	animation.set_loop(false);

	size.x = img->getwidth();
	size.y = img->getheight();

	size_explode.x = animation.get_atlas()->get_image(0)->getwidth();
	size_explode.y = animation.get_atlas()->get_image(0)->getheight();

	pos = { -100,-100 };

	damage = 10;
	energy = 5;

	speed = { 1,0 };



}

PeaBullet::~PeaBullet()
{
}

bool PeaBullet::check_collide(Point pos, Rect rect)
{
	const bool is_coll=Bullet::check_collide(pos,rect);
	if (is_coll) {
		is_valid=false;//…Ë÷√Œﬁ–ß
		switch (rand()%3)
		{
		case 0:
			mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
			break;
		default:
			mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
			break;
		}
	}
	if (!is_valid) {
		const int dir =speed.x / abs(speed.x);
		speed.x = 0.2*dir;
	}
	return is_coll;
}

bool PeaBullet::check_collide(Rect rect1, Rect rect2)
{
	return Bullet::check_collide(rect1, rect2);
}

void PeaBullet::on_update(int delta_time)
{
	pos.x += speed.x * delta_time;
	if (!is_valid) {
		if (!is_remove) {
			animation.on_update(delta_time);
		}
		if (animation.isend()) {
			is_remove = true;
			animation.reset();
		}
	}
}

void PeaBullet::on_draw(const Camera& camera)
{
	Bullet::on_draw(camera);
	if (is_valid) {
		putImage_alpha(camera, pos.x, pos.y, img);
	}
	else {
		const Point mid = { pos.x - size_explode.x / 2 + size.x / 2, pos.y - size_explode.y / 2 + size.y / 2 };
		if (!is_remove) {
			animation.on_draw(camera, mid.x, mid.y);
		}
	}
}
