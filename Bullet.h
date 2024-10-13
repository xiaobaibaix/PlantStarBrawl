#pragma once
#include "Vector2D.h"
#include <functional>
#include "Animation.h"
#include "Camera.h"
#include "Player.h"
#include "SceneManager.h"
#include "common.h"

extern bool is_debug;
extern SceneManager scene_manager;


class Bullet
{
public:
	friend class Player;
	Bullet()=default;
	virtual~Bullet();
	//位置
	void setPos(const Point& point);
	const Point& getPos();
	//伤害
	void setDamage(int damamge);
	int getDamage();
	//子弹大小	
	void setSize(const Vector2D& size);
	const Vector2D& getSize();
	//速度
	void setSpeed(const Vector2D& speed);
	const Vector2D& getSpeed();
	//攻击id
	void setTargetId(Player::PlayerId target);
	Player::PlayerId getTargetId();
	//子弹有效与否
	void setValid(bool valid);
	bool getValid();
	//子弹删除与否
	void setRemove(bool remove);
	bool getRemove();
	//id
	void setId(int id);
	int getId();
	//回调函数
	void setCallback(std::function<void()> callback);

	void reset();//重置
	void fire(Point pos, int dir);//开火

	virtual void on_collide();//碰撞到了

	virtual bool check_collide(Point pos, Rect rect);//检查碰撞
	virtual bool check_collide(Rect rect1, Rect rect2);//检查碰撞

	virtual void on_update(int delta_time)=0;
	virtual void on_draw(const Camera& camera);

	void check_out_screen();//检查出界

protected:
	int id = 0;//子弹id
	static int damage;//伤害
	static int energy;//伤害

	Point pos = {0};//位置
	Vector2D size = {0};//子弹大小
	Vector2D size_explode = { 0 };//爆炸范围
	Vector2D speed = {0};//子弹速度

	bool is_valid = true;//是否有效
	bool is_remove = false;//是否删除

	Player::PlayerId target_id=Player::PlayerId::invalid;//打击的目标玩家

	std::function<void()> callback;


};

