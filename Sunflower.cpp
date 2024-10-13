#include "Sunflower.h"
#include "Bullet.h"
#include "SunBullet.h"
#include "SunBulletEx.h"
#include <iostream>


extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_left;
extern Atlas atlas_sunflower_attack_right;
extern Atlas atlas_sunflower_die_left;
extern Atlas atlas_sunflower_die_right;

Sunflower::Sunflower(PlayerId id):Player(id)
{
	animation_idle[0].set_atlas(&atlas_sunflower_idle_left);
	animation_idle[1].set_atlas(&atlas_sunflower_idle_right);
	animation_idle[0].set_interval(100);
	animation_idle[1].set_interval(100);
	animation_idle[0].set_loop(true);
	animation_idle[1].set_loop(true);

	animation_run[0].set_atlas(&atlas_sunflower_run_left);
	animation_run[1].set_atlas(&atlas_sunflower_run_right);
	animation_run[0].set_interval(100);
	animation_run[1].set_interval(100);
	animation_run[0].set_loop(true);
	animation_run[1].set_loop(true);


	animation_attack[0].set_atlas(&atlas_sunflower_attack_left);
	animation_attack[1].set_atlas(&atlas_sunflower_attack_right);
	animation_attack[0].set_interval(100);
	animation_attack[1].set_interval(100);
	animation_attack[0].set_loop(true);
	animation_attack[1].set_loop(true);

	animation_die[0].set_atlas(&atlas_sunflower_die_left);
	animation_die[1].set_atlas(&atlas_sunflower_die_right);
	animation_die[0].set_interval(300);
	animation_die[1].set_interval(300);

	move_speed.x = 0.5;
	move_speed.y = 0;
	jump_speed = 1.5;

	shape.left_up = pos;
	shape.w = atlas_sunflower_idle_left.get_image(0)->getwidth();
	shape.h = atlas_sunflower_idle_left.get_image(0)->getheight();

	time_common = 500;
	time_attack = time_common *2;

	bullet_list.resize(10);
	timer.pause();
}

Sunflower::~Sunflower()
{
}

void Sunflower::on_update(int delta_time)
{
	Player::on_update(delta_time);

	time_cur += delta_time;
	//普通子弹
	if (!is_attack && is_common && time_cur >= time_common) {
		time_cur = 0;
		for (Bullet*& bullet : bullet_list) {

			if (bullet && bullet->getRemove()) {//已经被删除的子弹
				bullet->reset();
				bullet->setSpeed({ 0.5,-0.5 });
				bullet->fire(Point(pos.x- bullet->getSize().x/2+shape.w/2,pos.y), is_face_right ? 1 : -1);
				break;
			}
			else if (!bullet) {//子弹不足创建子弹
				Bullet* bull = new SunBullet();
				if (!bull)return;
				bull->setId(bull->getId() + 1);
				bullet = bull;
				if (id == Player::PlayerId::p1) {
					bullet->setTargetId(Player::PlayerId::p2);
				}
				else if (id == Player::PlayerId::p1) {
					bullet->setTargetId(Player::PlayerId::p1);
				}
				bullet->fire(Point(pos.x - bullet->getSize().x / 2 + shape.w / 2, pos.y), is_face_right ? 1 : -1);
				break;
			}
		}
	}
	if(sunBullet_ex&&!sunBullet_ex->getRemove())sunBullet_ex->on_update(delta_time);

}

void Sunflower::on_draw(const Camera& camera)
{
	Player::on_draw(camera);
	if (sunBullet_ex&&!sunBullet_ex->getRemove())sunBullet_ex->on_draw(camera);
}

void Sunflower::on_input(const ExMessage& msg)
{
	Player::on_input(msg);
}

std::vector<Player::BulletType> Sunflower::collision_bullet(const Player& another)
{
	std::vector<Player::BulletType> bullet_type_list=Player::collision_bullet(another);
	const Point pos_an = another.getPos();
	const Vector2D size_an = { static_cast<float>(another.getShape().w),static_cast<float>(another.getShape().h) };
	bool is_coll = false;
	if(sunBullet_ex&& sunBullet_ex->getValid())
		is_coll=sunBullet_ex->check_collide(
		Rect(
			Point(sunBullet_ex->getPos().x+ sunBullet_ex->getSize().x/4, sunBullet_ex->getPos().y + sunBullet_ex->getSize().y / 4),
			Point(sunBullet_ex->getPos().x+ sunBullet_ex->getSize().x - sunBullet_ex->getSize().x / 4, sunBullet_ex->getPos().y + sunBullet_ex->getSize().y - sunBullet_ex->getSize().y / 4)),//子弹矩形
		Rect(pos_an, pos_an+ size_an)//玩家矩形
	);
	if (is_coll) {
		bullet_type_list.push_back(Player::BulletType::SunBulletEx);
	}
	return bullet_type_list;
}

void Sunflower::on_attack()
{
	static bool is_run = false;
	if (is_attack&&!is_run) {
		is_run = true;
		EP = 0;
		timer.resume();
		timer.set_one_shot(true);
		timer.set_wait_time(1000);
		timer.set_callback([&]() {
			//std::cout << "time out" << std::endl;
			is_attack = false;
			is_run = false;
			});
		timer.restart();

		const int dir = is_face_right ? 1 : -1;
		if (!sunBullet_ex) {
			SunBulletEx *ex= new SunBulletEx;
			ex->reset();
			ex->getAniamtionText().reset();
			ex->setTextPos(pos);
			ex->setTextExist(true);
			sunBullet_ex = ex;
			if (sunBullet_ex) {
				if (id == Player::PlayerId::p1) {
					sunBullet_ex->setTargetId(Player::PlayerId::p2);
				}
				else if (id == Player::PlayerId::p2) {
					sunBullet_ex->setTargetId(Player::PlayerId::p1);
				}
			}
			sunBullet_ex->fire({ pos.x - sunBullet_ex->getSize().x / 2 + shape.w / 2 + sunBullet_ex_length * dir,-sunBullet_ex->getSize().y }, 0);
		}
		else {
			SunBulletEx* ex = dynamic_cast<SunBulletEx*>(sunBullet_ex);
			if (ex) {
				ex->reset();
				ex->getAniamtionText().reset();
				ex->setTextPos(pos);
				ex->setTextExist(true);
			}
			sunBullet_ex->fire({ pos.x - ex->getSize().x / 2 + shape.w / 2 + sunBullet_ex_length * dir,-sunBullet_ex->getSize().y }, 0);
		}
		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
	}
}
