#pragma once
#include "common.h"
#include "Vector2D.h"
#include "Player.h"


class WinnerBar
{
public:
	WinnerBar();
	~WinnerBar();

	void on_update(int delta_time);
	void on_draw();


	void setWinid(Player::PlayerId id);
	void setStop(bool is_stop);

	const Point& getPos();

private:

	Player::PlayerId win_id = Player::PlayerId::invalid;

	Point pos = {0};
	Vector2D move_speed = {0};
	
	bool is_stop = true;

	IMAGE* img_1p = nullptr;
	IMAGE* img_2p = nullptr;
	IMAGE* img_bar = nullptr;

};

