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
	int pass_time = 0;			//������ʱ��
	int wait_time = 0;			//ʱ����
	bool paused = false;		//�Ƿ���ͣ
	bool shotted = false;		//�Ƿ񱻴���
	bool one_shot = false;		//�Ƿ�һ�δٷ�
	std::function<void()> callback;//�ص�����
};

