#include "Player.h"
#include <iostream>
#include <algorithm >
#include "util.h"
#include "Platform.h"
#include "Bullet.h"
#include "PeaBullet.h"
#include "SunBullet.h"
#include "SunBulletEx.h"

extern bool is_debug;
//地板对象
extern std::vector<Platform> platforms;

extern Atlas atlas_run_effect;
extern Atlas atlas_jump_effect;
extern Atlas atlas_land_effect;


Player::Player(PlayerId id):id(id)
{
	init();
}

Player::~Player()
{
}

void Player::init()
{
	timer.pause();
	HP = max_hp;
	EP = 0;
	if (id == Player::PlayerId::p1) {
		is_face_right = true;
	}
	else if (id == Player::PlayerId::p2) {
		is_face_right = false;
	}

	if (is_face_right)animation_cur = &animation_idle[1];
	else animation_cur = &animation_idle[0];
}

void Player::reset()
{
	init();
	timer.restart();
	timer.pause();
	time_cur = 0;

	is_living = true;
	is_jumping = false;
	is_attack = false;
	is_common = false;

	is_jump = false;
	is_right = false;
	is_left = false;

	animation_cur->reset();

	switch (id)
	{
	case Player::PlayerId::invalid:
		break;
	case Player::PlayerId::p1:
		pos={ 280,50 };
		break;
	case Player::PlayerId::p2:
		pos = { 900,50 };
		break;
	default:
		break;
	}
}

void Player::on_update(int delta_time)
{
	//子弹更新
	for (Bullet*& bullet : bullet_list) {

		if (bullet && !bullet->getRemove()) {//正常更新的子弹
			bullet->check_out_screen();
			if (!bullet->getRemove())bullet->on_update(delta_time);
		}
		else if (!bullet) {
			break;
		}
	}

	const int dir = (is_right - is_left);

	if (pos.y+shape.h>=getheight()) {
		HP = 0;
	}

	if (HP<=0&&is_living) {
		is_living = false;
		//std::cout << "HP" << std::endl;
		move_speed.x = 0.5;
		move_speed.y = -1.5;
	}

	animation_cur->on_update(delta_time);
	timer.on_update(delta_time);

	if (is_living) {
		const float pre_y = shape.left_up.y + shape.h;
		on_run(delta_time);
		on_jump(delta_time);

		if ((dir == 1 and is_face_right == false) || (dir == -1 and is_face_right == true)) {
			if (is_face_right) {
				animation_cur = &animation_idle[0];
				is_face_right = false;
			}
			else {
				animation_cur = &animation_idle[1];
				is_face_right = true;
			}

		}
		else if ((dir == 1 and is_face_right == true) || (dir == -1 and is_face_right == false)) {
			if (is_face_right) {//右
				animation_cur = &animation_run[1];
			}
			else {//左
				animation_cur = &animation_run[0];
			}
		}
		if (dir == 0) {
			if (is_attack) {
				if (is_face_right) {
					animation_cur = &animation_attack[1];
				}
				else {
					animation_cur = &animation_attack[0];
				}
			}
			else {
				if (is_face_right) {
					animation_cur = &animation_idle[1];
				}
				else {
					animation_cur = &animation_idle[0];
				}
			}
		}

		if (pre_y <(shape.left_up.y + shape.h)&& (move_speed.y==0)) {

			if (particle_land) {
				if (!particle_land->isValid()) {
					particle_land->reset({ pos.x - atlas_land_effect.get_image(0)->getwidth() / 2 + shape.w / 2,pos.y - atlas_land_effect.get_image(0)->getheight() / 2 + shape.h / 2 - 10 });
					particle_land->fire();
				}
			}
			else {
				Particle* p = new Particle({ pos.x - atlas_land_effect.get_image(0)->getwidth() / 2 + shape.w / 2,pos.y - atlas_land_effect.get_image(0)->getheight() / 2 + shape.h / 2 - 10 }, 100, &atlas_land_effect);
				particle_land=p;
				p->fire();
			}
		}
	}
	else {

		if (is_face_right) {
			animation_cur = &animation_die[1];
		}
		else {
			animation_cur = &animation_die[0];
		}
		move_speed.y += fall_speed * delta_time;

		pos.y += move_speed.y * delta_time;

	}
	//粒子特效更新
	for (Particle* p : particle_list) {
		if (!p) break;
		p->on_update(delta_time);
	}
	for (Particle* p : particle_list_jump) {
		if (!p) break;
		p->on_update(delta_time);
	}
	if (particle_land && particle_land->isValid())particle_land->on_update(delta_time);

}

void Player::on_draw(const Camera& camera)
{
	//粒子特效渲染
	for (Particle* p : particle_list) {
		if (!p) break;
		if (p->isValid())p->on_draw(camera);
	}
	for (Particle* p : particle_list_jump) {
		if (!p) break;
		if (p->isValid())p->on_draw(camera);
	}
	animation_cur->on_draw(camera, pos.x, pos.y);

	if(particle_land&& particle_land->isValid())particle_land->on_draw(camera);
	if (is_debug) {
		drawRect(camera, shape.left_up, Point(shape.left_up.x+shape.w,shape.left_up.y+shape.h));
	}
}

void Player::on_input(const ExMessage& msg)
{
	if (id == PlayerId::p1) {
		switch (msg.message)
		{
		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case 0x41://A
				is_left = false;
				break;
			case 0x44://D
				is_right = false;
				break;
			//case 0x51:
			//	is_attack = false;
				//break;
			case 0x45:
				is_common = false;
				break;
			case 0x57://跳
				is_jump = false;
				break;
			default:
				break;
			}
			break;
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case 0x41://A
				is_left = true;
				break;
			case 0x44://D
				is_right = true;
				break;
			case 0x51://attack
				if (is_common)break;
				if(!is_attack&&(EP>=max_ep))is_attack = true;
				on_attack();
				break;
			case 0x45:
				if (is_attack)break;
				if(!is_common)is_common = true;
				break;
			case 0x57://跳
				is_jump = true;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else if (id == PlayerId::p2) {
		switch (msg.message)
		{
		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case VK_LEFT://A
				is_left = false;
				break;
			case VK_RIGHT://D
				is_right = false;
				break;
			//case VK_NUMPAD1:
			//	is_attack = false;
			//	break;
			case VK_NUMPAD2://attack
				is_common = false;
				break;
			case VK_UP://跳
				is_jump = false;
				break;
			default:
				break;
			}
			break;
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case VK_LEFT://A
				is_left = true;
				break;
			case VK_RIGHT://D
				is_right = true;
				break;
			case VK_NUMPAD1://attack
				if (is_common)break;
				if(!is_attack&&max_ep<=EP)is_attack = true;
				on_attack();
				break;
			case VK_NUMPAD2://attack
				if (is_attack)break;
				if(!is_common)is_common = true;
				break;
			case VK_UP://跳
				is_jump = true;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Player::on_jump(int delta_time)
{
	if (move_speed.y == 0 && is_jump&& !is_jumping) {
		move_speed.y -= jump_speed;
		is_jump = false;
		is_jumping = true;

		if (particle_list_jump.empty()) {
			//std::cout << "create" << std::endl;
			Particle* p = new Particle({ pos.x - atlas_jump_effect.get_image(0)->getwidth() / 2 + shape.w / 2,pos.y - atlas_jump_effect.get_image(0)->getheight() / 2 + shape.h / 2 - 10 }, 100, &atlas_jump_effect);
			particle_list_jump.push_back(p);
			p->fire();
		}
		else {
			for (int i = 0; i < particle_list_jump.size(); i++) {
				if (!particle_list_jump.at(i)->isValid()) {
					//std::cout << "reset" << std::endl;
					particle_list_jump.at(i)->reset({ pos.x - atlas_jump_effect.get_image(0)->getwidth() / 2 + shape.w / 2,pos.y - atlas_jump_effect.get_image(0)->getheight() / 2 + shape.h / 2 - 10 });
					particle_list_jump.at(i)->fire();
					break;
				}
				else {
					//std::cout << "continue" << std::endl;
					continue;
				}
			}
			Particle* p = new Particle({ pos.x - atlas_jump_effect.get_image(0)->getwidth() / 2 + shape.w / 2,pos.y - atlas_jump_effect.get_image(0)->getheight() / 2 + shape.h / 2 - 10 }, 100, &atlas_jump_effect);
			particle_list_jump.push_back(p);
			p->fire();
		}
	}
	if (move_speed.y == 0&&!is_jump) {
		is_jumping = false;
	}

	pos.y += move_speed.y * delta_time*0.01;
	shape.left_up = pos;
}

void Player::on_run(int delta_time)
{
	const float pre_y = shape.left_up.y+shape.h;
	const int dir = (is_right - is_left);

	move_speed.y += fall_speed * delta_time;

	pos.x += move_speed.x * delta_time * dir;
	pos.y += move_speed.y * delta_time;

	shape.left_up = pos;

	collision(pre_y);

	//粒子特效
	static int t = 0;
	t += delta_time;
	if (dir != 0 &&t>= time_particle) {
		//std::cout << "create" << std::endl;
		t = 0;
		if (particle_list.empty()) {
			//std::cout << "create" << std::endl;
			Particle* p = new Particle({pos.x- atlas_run_effect .get_image(0)->getwidth()/2+shape.w/2,pos.y - atlas_run_effect.get_image(0)->getheight() / 2 + shape.h / 2-10 }, 100, &atlas_run_effect);
			particle_list.push_back(p);
			p->fire();
		}
		else {
			for (int i = 0; i < particle_list.size();i++) {
				if (!particle_list.at(i)->isValid()) {
					//std::cout << "reset" << std::endl;
					particle_list.at(i)->reset({ pos.x - atlas_run_effect.get_image(0)->getwidth() / 2 + shape.w / 2,pos.y - atlas_run_effect.get_image(0)->getheight() / 2 + shape.h / 2 - 10 });
					particle_list.at(i)->fire();
					break;
				}
				else {
					//std::cout << "continue" << std::endl;
					continue;
				}
			}
			Particle* p = new Particle({ pos.x - atlas_run_effect.get_image(0)->getwidth() / 2 + shape.w / 2,pos.y - atlas_run_effect.get_image(0)->getheight() / 2 + shape.h / 2-10 }, 100, &atlas_run_effect);
			particle_list.push_back(p);
			p->fire();
		}
	}

}

void Player::on_attack()
{

}

void Player::collision(float pre_y)
{
	bool is_collision = false;
	float coll_y = 0;
	//碰撞检测
	if (move_speed.y > 0 || move_speed.y==0) {
		is_collision = check(pre_y,&coll_y);
	}
	if (is_collision) {
		pos.y = coll_y - 1;
		move_speed.y = 0;
	}
}

void Player::on_collision_from(BulletType type)
{
	switch (type)
	{
	case Player::BulletType::valid:
		break;
	case Player::BulletType::PeaBullet:
		this->HP -= PeaBullet::damage;
		break;
	case Player::BulletType::SunBullet:
		this->HP -= SunBullet::damage;
		break;
	case Player::BulletType::SunBulletEx:
		this->HP -= SunBulletEx::damage;
		break;
	default:
		break;
	}
}

void Player::on_collision_to(BulletType type)
{
	switch (type)
	{
	case Player::BulletType::valid:
		break;
	case Player::BulletType::PeaBullet:
		this->EP += PeaBullet::energy;
		break;
	case Player::BulletType::SunBullet:
		this->EP += SunBullet::energy;
		break;
	case Player::BulletType::SunBulletEx:
		this->EP += SunBulletEx::energy;
		break;
	default:
		break;
	}
}

std::vector<Player::BulletType> Player::collision_bullet(const Player& another)
{
	std::vector<Player::BulletType> bullet_type_list;
	for(Bullet* bull : bullet_list)
	{
		if (bull && bull->getValid()) {
			const float mid_x = bull->getPos().x + bull->getSize().x / 2;
			const float mid_y = bull->getPos().y + bull->getSize().y / 2;

			const bool is_coll = bull->check_collide(
				Point(mid_x, mid_y),//子弹点
				Rect(Point(another.pos.x + another.shape.w/4, another.pos.y + another.shape.h / 4),Point(another.pos.x + another.shape.w - another.shape.w / 4, another.pos.y + another.shape.h - another.shape.w / 4))
			);//玩家矩形

			if (is_coll) {
				bullet_type_list.push_back(Player::BulletType::PeaBullet);
			}
		}
	}
	return bullet_type_list;
}

bool Player::check(float pre_y, float *coll_y)
{
	for (const Platform& platform:platforms) {
		const Platform::CollisionShape& shape_ = platform.shape;
		if ((shape_.y >= shape.left_up.y )&& (shape_.y <= shape.left_up.y + shape.h)) {
			if ((shape_.left<=shape.left_up.x+shape.w)&&(shape_.right>=shape.left_up.x)) {
				if (pre_y <shape_.y) {
					*coll_y = shape_.y-shape.h;
					return true;
				}
			}
		}
	}
	return false;
}


void Player::drawRect(const Camera& camera,Point p1, Point p2)
{
	line(camera, p1.x, p1.y, p2.x, p1.y);
	line(camera, p1.x, p1.y, p1.x, p2.y);
	line(camera, p2.x, p1.y, p2.x, p2.y);
	line(camera, p1.x, p2.y, p2.x, p2.y);
}

void Player::setPos(Point pos)
{
	this->pos = pos;
}

const Point& Player::getPos()const
{
	return pos;
}

const std::vector<Bullet*>& Player::getBullet_list()
{
	return bullet_list;
}

const Player::CollisionShape& Player::getShape() const
{
	return shape;
}
