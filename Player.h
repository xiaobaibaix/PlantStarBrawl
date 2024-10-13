#pragma once
#include "common.h"
#include "Camera.h"
#include "Animation.h"
#include "Particle.h"

class Bullet;
class Player
{
public:
	friend class StateBar;
	friend class GameScene;

	struct CollisionShape
	{
		Point left_up;
		int w;
		int h;
	};

	enum class PlayerId
	{
		invalid,
		p1,
		p2
	};

	enum class BulletType
	{
		valid,
		PeaBullet,
		SunBullet,
		SunBulletEx
	};

public:
	Player()=default;
	Player(PlayerId id);
	virtual~Player();

	void init();
	void reset();

	void setPos(Point pos);
	const Point& getPos()const;
	const std::vector<Bullet* >& getBullet_list();

	virtual void on_update(int delta_time) ;
	virtual void on_draw(const Camera& camera) ;
	virtual void on_input(const ExMessage& msg) ;

	void on_jump(int delta_time);
	void on_run(int delta_time);
	virtual void on_attack();

	bool check(float pre_y, float* coll_y);
	void collision(float pre_y);
	virtual void on_collision_from(BulletType type);
	virtual void on_collision_to(BulletType type);
	virtual std::vector<BulletType> collision_bullet(const Player& another);

	const Player::CollisionShape& getShape()const;

private:
	void drawRect(const Camera& camera, Point p1, Point p2);

public:
	PlayerId id;
protected:

	Point pos = { 0 };//对象位置
	Vector2D move_speed = {0,0};
	CollisionShape shape = { 0 };

	float jump_speed = 0;

	const float fall_speed = 0.005;

	Animation animation_idle[2];
	Animation animation_run[2];
	Animation animation_attack[2];
	Animation animation_die[2];

	Animation *animation_cur=nullptr;

	bool is_left = false;
	bool is_right = false;
	bool is_jump = false;
	bool is_attack = false;
	bool is_common = false;

	bool is_jumping = false;
	bool is_living = true;

	bool is_face_right = false;

	int time_common = 0;//普通攻击时间间隔
	int time_attack = 0;//pea大招发射时间间隔
	int time_cur=0;
	int time_particle = 100;//粒子发射时间间隔

	int HP = 0;//血量
	int EP = 0;//能量

	const int max_hp = 200;
	const int max_ep = 100;

	Timer timer;

	std::vector<Bullet* > bullet_list;//子弹列表
	std::vector<Particle*> particle_list;//特效粒子run列表
	std::vector<Particle*> particle_list_jump;//特效粒子jump列表
	Particle* particle_land= nullptr;//特效粒子land列表

};

