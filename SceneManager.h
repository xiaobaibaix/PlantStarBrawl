#pragma once
#include "Scene.h"

class SceneManager
{
public:
	friend class SelectScene;
	friend class Player;
	enum class Scenetype
	{
		Menu,
		Game,
		Select
	};
public:

	SceneManager();
	~SceneManager();

	void set_current_scene(Scene* scene);
	void switch_to(Scenetype type);

	void on_update(int drlta_time);
	void on_input(const ExMessage& msg);
	void on_draw();

	Camera& getCmaera();
private:
	Scene* current_state = nullptr;
	
	Camera camera = {0};
};

