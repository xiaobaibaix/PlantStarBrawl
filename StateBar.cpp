#include "StateBar.h"
#include "util.h"
#include "Player.h"


StateBar::StateBar(Point pos):pos(pos)
{
}

StateBar::~StateBar()
{
}

float StateBar::getHP()
{
	return HP_percent;
}

float StateBar::getEP()
{
	return EP_percent;
}

const Point& StateBar::getPos()
{
	return pos;
}

const IMAGE& StateBar::getImg()
{
	return *img;
}

int StateBar::getLength()
{
	return length;
}

const Vector2D& StateBar::getSize()
{
	return img_size;
}

void StateBar::setHP(float hp)
{
	HP_percent = hp;
}

void StateBar::setEP(float ep)
{
	EP_percent = ep;
}

void StateBar::setPos(Point pos)
{
	this->pos = pos;
}

void StateBar::setImg(IMAGE* img)
{
	this->img = img;
	img_size.x = img->getwidth();
	img_size.y = img->getheight();
}

void StateBar::on_update(int delta_time, const Player& player)
{
	HP_percent = (player.HP / (float)player.max_hp)>=1? 1 : player.HP / (float)player.max_hp;
	EP_percent = (player.EP / (float)player.max_ep)>=1? 1 : player.EP / (float)player.max_ep;
}

void StateBar::on_draw()
{
	if (img)putImage_alpha(pos.x, pos.y, img);
	const int p = 3;
	const int p2 = 10;
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);

	//setlinecolor(RGB(45, 45, 45));
	//rectangle(pos.x + img_size.x+ p, pos.y+ p+ p2, pos.x + img_size.x + length+ p, pos.y + img_size.y / 2+ p - p2);
	setlinecolor(BLACK);
	rectangle(pos.x + img_size.x, pos.y+ p2, pos.x + img_size.x + length, pos.y + img_size.y / 2- p2);
	setfillcolor(RED);
	solidrectangle(pos.x + img_size.x, pos.y+ p2, (pos.x + img_size.x + length * HP_percent)<= (pos.x + img_size.x) ? pos.x + img_size.x : pos.x + img_size.x + length * HP_percent, pos.y + img_size.y / 2- p2);

	//setlinecolor(RGB(45, 45, 45));
	//rectangle(pos.x + img_size.x + p, pos.y + p + p2, pos.x + img_size.x + length + p, pos.y + img_size.y / 2 + p - p2);
	setlinecolor(BLACK);
	rectangle(pos.x + img_size.x, pos.y + img_size.y / 2 + p2, pos.x + img_size.x + length, pos.y + img_size.y  - p2);
	setfillcolor(BLUE);
	solidrectangle(pos.x + img_size.x, pos.y + img_size.y / 2+ p2, (pos.x + img_size.x + length * EP_percent) <= (pos.x + img_size.x) ? pos.x + img_size.x : pos.x + img_size.x + length * EP_percent, pos.y + img_size.y- p2);
}
