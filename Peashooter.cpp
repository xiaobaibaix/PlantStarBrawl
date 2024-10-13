#include "Peashooter.h"
#include "PeaBullet.h"
#include "SceneManager.h"
#include <iostream>

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_attack_left;
extern Atlas atlas_peashooter_attack_right;
extern Atlas atlas_peashooter_die_left;
extern Atlas atlas_peashooter_die_right;

extern SceneManager scene_manager;

Peashooter::Peashooter(PlayerId id):Player(id)
{
	animation_idle[0].set_atlas(&atlas_peashooter_idle_left);
	animation_idle[1].set_atlas(&atlas_peashooter_idle_right);
	animation_idle[0].set_interval(100);
	animation_idle[1].set_interval(100);
	animation_idle[0].set_loop(true);
	animation_idle[1].set_loop(true);

	animation_run[0].set_atlas(&atlas_peashooter_run_left);
	animation_run[1].set_atlas(&atlas_peashooter_run_right);
	animation_run[0].set_interval(100);
	animation_run[1].set_interval(100);
	animation_run[0].set_loop(true);
	animation_run[1].set_loop(true);


	animation_attack[0].set_atlas(&atlas_peashooter_attack_left);
	animation_attack[1].set_atlas(&atlas_peashooter_attack_right);
	animation_attack[0].set_interval(100);
	animation_attack[1].set_interval(100);
	animation_attack[0].set_loop(true);
	animation_attack[1].set_loop(true);

	animation_die[0].set_atlas(&atlas_peashooter_die_left);
	animation_die[1].set_atlas(&atlas_peashooter_die_right);
	animation_die[0].set_interval(300);
	animation_die[1].set_interval(300);

	move_speed.x = 0.5;
	move_speed.y = 0;
	jump_speed = 1.5;

	shape.left_up = pos;
	shape.w = atlas_peashooter_idle_left.get_image(0)->getwidth();
	shape.h = atlas_peashooter_idle_left.get_image(0)->getheight();

	time_common = 500;
	time_attack = time_common/4;


	bullet_list.resize(40);
}

Peashooter::~Peashooter()
{

}

void Peashooter::on_attack()
{
	static bool is_run = false;
	if (is_attack&& !is_run) {
		is_run = true;
		EP = 0;
		timer.resume();
		timer.set_one_shot(true);
		timer.set_wait_time(2500);
		timer.set_callback([&]() {
			//std::cout << "time out" << std::endl;
			is_attack = false;
			is_run = false;
			});
		timer.restart();

		mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);


		//std::cout << "抖动" << std::endl;
		scene_manager.getCmaera().setJitter_TimeAndR(2500, 2);
		scene_manager.getCmaera().setJitterStart(true);
		scene_manager.getCmaera().getTimer().set_one_shot(true);
		scene_manager.getCmaera().getTimer().set_wait_time(scene_manager.getCmaera().getJitterTime());
		scene_manager.getCmaera().getTimer().restart();
	}
}

void Peashooter::on_update(int delta_time)
{
	Player::on_update(delta_time);

	time_cur += delta_time;
	if (!is_attack && is_common && time_cur >= time_common) {
		//std::cout << "play" << std::endl;
		switch (rand() % 2)
		{
		case 0:
			mciSendString(_T("play pea_shoot_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_shoot_2 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	}

	if ((!is_common&&is_attack && time_cur >= time_attack)||(!is_attack && is_common && time_cur >= time_common)) {
		time_cur = 0;
		
		for (Bullet*& bullet : bullet_list) {

			if (bullet && bullet->getRemove()) {//已经被删除的子弹
				bullet->reset();
				bullet->setSpeed({ 1,0 });
				bullet->fire(Point(pos.x - bullet->getSize().x / 2 + shape.w / 2, pos.y), is_face_right ? 1 : -1);
				break;
			}
			else if (!bullet) {//子弹不足创建子弹
				Bullet* bull = new PeaBullet();
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
}

void Peashooter::on_draw(const Camera& camera)
{
	Player::on_draw(camera);

}

void Peashooter::on_input(const ExMessage& msg)
{
	Player::on_input(msg);
	
}