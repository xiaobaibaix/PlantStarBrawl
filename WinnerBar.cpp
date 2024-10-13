#include "WinnerBar.h"
#include "util.h"

extern IMAGE img_1p_winner;
extern IMAGE img_2p_winner;
extern IMAGE img_winner_bar;


WinnerBar::WinnerBar()
{
	this->img_1p = &img_1p_winner;
	this->img_2p = &img_2p_winner;
	this->img_bar = &img_winner_bar;

	pos = {0,getheight()/2.0f};
	move_speed = {1000,0};
}

WinnerBar::~WinnerBar()
{

}
//38.4(x-4)^2
void WinnerBar::on_update(int delta_time)
{
	if (!is_stop) {
		pos.x += move_speed.x * delta_time / 1000;
	}
}

void WinnerBar::on_draw()
{
	putImage_alpha(pos.x- img_bar->getwidth(), pos.y- img_bar->getheight()/2, img_bar);
	switch (win_id)
	{
	case Player::PlayerId::invalid:
		break;
	case Player::PlayerId::p1:
		putImage_alpha(pos.x - img_bar->getwidth()- img_1p->getwidth()/2+ img_bar->getwidth()/2, pos.y - img_1p->getheight() / 2, img_2p);
		break;
	case Player::PlayerId::p2:
		putImage_alpha(pos.x - img_bar->getwidth() - img_2p->getwidth() / 2 + img_bar->getwidth() / 2, pos.y - img_2p->getheight() / 2, img_1p);
		break;
	default:
		break;
	}
}

void WinnerBar::setWinid(Player::PlayerId id)
{
	win_id = id;
}

void WinnerBar::setStop(bool is_stop)
{
	this->is_stop = -is_stop;
}

const Point& WinnerBar::getPos()
{
	return pos;
}
