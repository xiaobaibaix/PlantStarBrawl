#pragma once
#include "Atlas.h"
#include "util.h"


class Animation
{
public:
	Animation()=default;
	~Animation() = default;
public:
	void reset();

	Atlas* get_atlas()const;

	void set_atlas(Atlas* new_atlas);	//设置图集
	void set_loop(bool flag);			//设置是否循环
	void set_loop(bool flag,int count);	//设置是否循环
	void set_interval(int ms);			//设置帧间隔
	bool isend();						//是否播放结束

	void on_update(int delta);			//动画更新
	void on_draw(const Camera& camera,int x, int y)const;//动画绘制

private:
	int timer = 0;				//计时器
	int interval = 0;			//帧间隔
	int idx_frame = 0;			//帧索引
	int count = 1;				//播放次数

	bool is_loop = false;		//是否循环
	bool is_end = false;		//是否播放结束

	Atlas* atlas = nullptr;
};

