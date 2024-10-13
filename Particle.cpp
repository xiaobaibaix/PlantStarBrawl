#include "Particle.h"
#include "util.h"

Particle::Particle(Point pos, int time, Atlas* atlas):pos(pos),time_continue(time), atlas(atlas)
{

}

void Particle::reset(Point pos)
{
	is_valid = true;
	this->pos = pos;
	idx_frame = 0;
}

void Particle::setTime_continue(int time)
{
	time_continue = time;
}

void Particle::setAtlas(Atlas* atlas)
{
	this->atlas = atlas;
}

const Atlas& Particle::getAtlas()
{
	return *atlas;
}

bool Particle::isValid()
{
	return is_valid;
}

void Particle::setPos(Point pos)
{
	this->pos = pos;
}

const Point& Particle::getPos()
{
	return pos;
}

void Particle::fire()
{
	is_valid = true;
	timer = 0;
}

void Particle::on_update(int delta_time)
{
	if (!is_valid)return;
	timer += delta_time;
	if (timer>= time_continue) {
		timer = 0;
		idx_frame++;
		if (idx_frame>=atlas->get_size()) {
			idx_frame = atlas->get_size() - 1;
			is_valid = false;
		}
	}
}

void Particle::on_draw(const Camera& camera)
{
	putImage_alpha(camera, (int)pos.x, (int)pos.y, atlas->get_image(idx_frame));
	if (is_debug){
		drawRect(camera, pos, { pos.x + atlas->get_image(0)->getwidth(),pos.y + atlas->get_image(0)->getheight() });
	}
}
