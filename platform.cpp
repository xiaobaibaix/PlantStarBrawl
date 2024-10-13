#include "Platform.h"
#include"util.h"
extern bool is_debug;

void Platform::on_draw(const Camera& camera)
{
	putImage_alpha(camera,pos.x,pos.y,img);
	if (is_debug) {
		line(camera, shape.left, shape.y, shape.right, shape.y);
	}
}
