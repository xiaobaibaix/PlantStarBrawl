#pragma once
#include "Atlas.h"
#include "Vector2D.h"
#include "Camera.h"

extern bool is_debug;

class Particle
{
public:
	Particle() = default;
	Particle(Point pos,int time, Atlas* atlas);
	~Particle()=default;

	void reset(Point pos);

	void setTime_continue(int time);
	void setAtlas(Atlas* atlas);
	const Atlas& getAtlas();
	bool isValid();

	void setPos(Point pos);
	const Point& getPos();

	void fire();

	virtual void on_update(int delta_time);
	virtual void on_draw(const Camera& camera);



private:
	int timer = 0;				//计时器
	int time_continue = 0;		//帧间隔
	int idx_frame = 0;			//帧索引
	Point pos = {0};
	bool is_valid = false;		//是否有效
	Atlas* atlas = nullptr;
};

