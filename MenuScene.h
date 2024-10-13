#pragma once
#include "Scene.h"


class MenuScene :public Scene
{
public:
	MenuScene();
	~MenuScene();

	void on_enter()override;
	void on_update(int delta_time)override;
	void on_draw(const Camera& camera)override;
	void on_input(const ExMessage& msg)override;
	void on_exit()override;

private:

};

