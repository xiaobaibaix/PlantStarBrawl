#include "Animation.h"

void Animation::reset() {
	timer = 0;
	idx_frame = 0;
	is_end = false;		
}
void Animation::set_atlas(Atlas* new_atlas) {
	if (new_atlas) {
		atlas = new_atlas;
		reset();
	}
}
Atlas* Animation::get_atlas()const
{
	return atlas;
}
void Animation::set_loop(bool flag) {
	is_loop = flag;
	if (flag) {
		count = -1;
	}
}
void Animation::set_loop(bool flag, int count)
{
	is_loop = flag;
	if (flag) {
		count = -1;
	}
	else {
		this->count = count;
	}
}
void Animation::set_interval(int ms) {
	interval = ms;
}

bool Animation::isend()
{
	return is_end;
}

void Animation::on_update(int delta)
{
	static int count_ = 1;
	timer += delta;
	if (timer>=interval) {
		timer = 0;
		idx_frame++;
		if (idx_frame>=atlas->get_size()-1) {
			if (is_loop) {
				idx_frame = 0;
			}
			else if (!is_loop) {
				if (count_ < count) {
					idx_frame = 0;
					count_++;
				}
				else {
					idx_frame = atlas->get_size() - 1;
					count_ = 1;
					is_end = true;
				}
			}
		}
	}
}

void Animation::on_draw(const Camera& camera,int x, int y) const
{
	putImage_alpha(camera,x, y, atlas->get_image(idx_frame));
}
