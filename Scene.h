#pragma once
#include <graphics.h>
#include <iostream>
#include "Camera.h"

extern bool is_debug;

class Scene
{
public:
	Scene() = default;
	virtual~Scene()=default;

	virtual void on_enter() {};
	virtual void on_update(int delta_time) {};
	virtual void on_draw(const Camera&camera) {};
	virtual void on_input(const ExMessage& msg) {};
	virtual void on_exit() {};

private:

};

