#pragma once
#include "Camera.h"

class Platform
{
public:
	Platform()=default;
	~Platform()= default;
public:
	struct CollisionShape
	{
		float y;
		float left, right;
	};

	void on_draw(const Camera& camera);
public:
	CollisionShape shape = {0};
	IMAGE* img = nullptr;
	Point pos = {0};

};

