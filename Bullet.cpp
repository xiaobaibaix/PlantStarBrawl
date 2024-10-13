#include "Bullet.h"
#include "util.h"
#include <graphics.h>
#include <iostream>

extern bool is_debug;

int Bullet::damage;//ÉËº¦
int Bullet::energy;//ÉËº¦

Bullet::~Bullet()
{
}

void Bullet::setPos(const Point& point)
{
	this->pos = pos;
}

const Point& Bullet::getPos()
{
	return pos;
}

void Bullet::setDamage(int damamge)
{
	this->damage = damamge;
}

int Bullet::getDamage()
{
	return damage;
}

void Bullet::setSize(const Vector2D& size)
{
	this->size = size;
}

const Vector2D& Bullet::getSize()
{
	return size;
}

void Bullet::setSpeed(const Vector2D& speed)
{
	this->speed = speed;
}

const Vector2D& Bullet::getSpeed()
{
	return speed;
}

void Bullet::setTargetId(Player::PlayerId target)
{
	this->target_id = target;
}

Player::PlayerId Bullet::getTargetId()
{
	return target_id;
}

void Bullet::setValid(bool valid)
{
	is_valid = valid;
}

bool Bullet::getValid()
{
	return is_valid;
}

void Bullet::setRemove(bool remove)
{
	is_remove = remove;
}

bool Bullet::getRemove()
{
	return is_remove;
}

void Bullet::setId(int id)
{
	this->id = id;
}

int Bullet::getId()
{
	return id;
}

void Bullet::setCallback(std::function<void()> callback)
{
	this->callback = callback;
}

void Bullet::reset()
{
	pos = { -100,-100 };

	is_valid = true;
	is_remove = false;
}

void Bullet::fire(Point pos, int dir)
{
	this->pos = pos;
	speed.x *= dir;
	this->is_valid = true;
	this->is_remove = false;
}

void Bullet::on_collide()
{
	if (callback) {
		callback();
	}
}

bool Bullet::check_collide(Point pos, Rect rect)
{
	if (pos.x>=rect.getLeftUp().x&&pos.x<=rect.getRightDown().x
		&&pos.y>=rect.getLeftUp().y&&pos.y<=rect.getRightDown().y) {
		return true;
	}
	return false;
}

bool Bullet::check_collide(Rect rect1, Rect rect2)
{
	return (rect1.getLeftUp().x < rect2.getRightDown().x) &&
		(rect1.getRightDown().x > rect2.getLeftUp().x) &&
		(rect1.getLeftUp().y < rect2.getRightDown().y) &&
		(rect1.getRightDown().y > rect2.getLeftUp().y);
}


void Bullet::on_draw(const Camera& camera)
{
	if (is_debug) {
		drawRect(camera, pos, { pos.x + size.x,pos.y + size.y });
	}
}

void Bullet::check_out_screen()
{
	if ((pos.x+ size.x<=0||pos.x>getwidth())||(pos.y+size.y<=0||pos.y>getheight())) {
		//std::cout << "remove" << std::endl;
		is_remove = true;
	}
}
