#pragma once
#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;
public:
	void restart();
	void set_wait_time(int val);
	void set_one_shot(bool flag);
	void set_callback(std::function<void()> callback);
	void pause();
	void resume();
	void on_update(int delta);
	void start();
private:
	int pass_time = 0;			//经过的时间
	int wait_time = 0;			//时间间隔
	bool paused = false;		//是否暂停
	bool shotted = false;		//是否被触发
	bool one_shot = false;		//是否一次促发
	std::function<void()> callback;//回调函数
};

