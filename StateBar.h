#pragma once
#include <graphics.h>
#include "Vector2D.h"


class Player;
class StateBar
{
public:
	StateBar(Point pos);
	StateBar()=default;
	~StateBar();

	float getHP();
	float getEP();
	const Point& getPos();
	const IMAGE& getImg();
	int getLength();
	const Vector2D& getSize();

	void setHP(float hp);
	void setEP(float ep);
	void setPos(Point pos);
	void setImg(IMAGE* img);

	void on_update(int delta_time,const Player& player);
	void on_draw();
private:

	float HP_percent = 0;
	float EP_percent = 0;

	const int length = 200;
	Vector2D img_size = {0};
	IMAGE* img = nullptr;
	Point pos = {0};
};

