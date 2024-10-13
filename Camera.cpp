#include "Camera.h"
#include <time.h>
#include <random>

Vector2D ori_pos;

void Camera::reset() {
	cur_pos.x = 0;
	cur_pos.y = 0;
}

void Camera::on_update(int delta_time) {
	timer.on_update(delta_time);
	if (isJitter) {
		const  int rand_num_x = rand() % (this->getJitterRadius() * 2 + 1) - this->getJitterRadius();
		const int rand_num_y = rand() % (this->getJitterRadius() * 2 + 1) - this->getJitterRadius();
		this->setPosition(ori_pos.x + rand_num_x, ori_pos.y + rand_num_y);
	}
}

void Camera::on_enter()
{
	ori_pos = this->get_position();
	srand(time(0));
	//setJitter_TimeAndR(200, 10);
	timer.set_callback([=]() {
		isJitter = false;
		this->reset();
		});
}

void Camera::on_input(const ExMessage& msg)
{
	if (msg.message== WM_LBUTTONDOWN) {
		this->setJitterStart(true);
		timer.set_one_shot(true);
		timer.set_wait_time(JitterTime);
		timer.restart();
	}
}

const Vector2D& Camera::get_position()const
{
	return this->cur_pos;
}

int Camera::getJitterRadius()
{
	return JitterRadius;
}

Timer& Camera::getTimer()
{
	return timer;
}

int Camera::getJitterTime()
{
	return JitterTime;
}

void Camera::setPosition(int x, int y)
{
	this->cur_pos.x = x;
	this->cur_pos.y = y;
}

void Camera::setJitter_TimeAndR(int time, int r)
{
	JitterTime = time;
	JitterRadius = r;
}

void Camera::setJitterStart(bool flag)
{
	isJitter = true;
}

Camera::Camera()
{
	cur_pos.x = 0;cur_pos.y=0;
	on_enter();
}

Camera::Camera(Vector2D pos)
{
	this->cur_pos = pos;
	on_enter();
}

Camera::Camera(float x, float y)
{
	cur_pos.x = x;
	cur_pos.y = y;
	on_enter();
}
