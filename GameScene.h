#pragma once
#include "Scene.h"
#include "SelectScene.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "StateBar.h"
#include "WinnerBar.h"

class GameScene :
    public Scene
{
public:
	GameScene();
	~GameScene();

	void on_enter()override;
	void on_update(int delta_time)override;
	void on_draw(const Camera& camera)override;
	void on_input(const ExMessage& msg)override;
	void on_exit()override;

	void setPlayer(SelectScene::PlayerType p1, SelectScene::PlayerType p2);

private:
	void reset();
	void check_collision();

private:
	POINT sky_pos = { 0 };
	POINT hill_pos = { 0 };

	bool is_win=false;
	bool is_con = false;//ÊÇ·ñ¼ÌÐø

	Player* player1 = nullptr;
	Player* player2 = nullptr;

	StateBar* player_bar1 = nullptr;
	StateBar* player_bar2 = nullptr;

	WinnerBar winbar;
};

