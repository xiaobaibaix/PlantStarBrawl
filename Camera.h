#pragma once
#include "Vector2D.h"
#include "Timer.h"
#include <graphics.h>

class Camera
{
public:
	Camera();
	Camera(Vector2D pos);
	Camera(float x,float y);
	~Camera() = default;

	void reset();

	void on_update(int delta_time);
	void on_enter();
	void on_input(const ExMessage& msg);

public:
	const Vector2D& get_position()const;
	int  getJitterRadius();
	Timer& getTimer();
	int getJitterTime();

	void setPosition(int x, int y);
	void setJitter_TimeAndR(int time,int r);
	void setJitterStart(bool flag);//抖动开始

private:
	bool isJitter = false;	//是否抖动
	int JitterTime = 0;		//抖动时间
	int JitterRadius=0;		//抖动半径
	Vector2D cur_pos;		//当前坐标
	Timer timer;			//定时器
};

