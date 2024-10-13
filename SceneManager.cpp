#include "SceneManager.h"
extern Scene* menu_scene;
extern Scene* game_scene;
extern Scene* select_scene;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
}

void SceneManager::set_current_scene(Scene* scene)
{
	current_state = scene;
	current_state->on_enter();
	camera.on_enter();
}

void SceneManager::switch_to(Scenetype type)
{
	current_state->on_exit();
	switch (type) {
	case Scenetype::Menu:
		current_state = menu_scene;
		break;
	case Scenetype::Game:
		current_state = game_scene;
		break;
	case Scenetype::Select:
		current_state = select_scene;
		break;
	}
	camera.on_enter();
	current_state->on_enter();
}

void SceneManager::on_update(int delta_time)
{
	current_state->on_update(delta_time);
	camera.on_update(delta_time);
}

void SceneManager::on_input(const ExMessage& msg)
{
	current_state->on_input(msg);
}

void SceneManager::on_draw()
{
	current_state->on_draw(camera);
}

Camera& SceneManager::getCmaera()
{
	return camera;
}

