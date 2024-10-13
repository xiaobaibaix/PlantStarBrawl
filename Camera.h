#pragma once
#include "Vector2D.h"
#include "Timer.h"
#include <graphics.h>

class Camera
{
public:
	Camera();
	Camera(Vector2D pos);
	Camera(float x,float y);
	~Camera() = default;

	void reset();

	void on_update(int delta_time);
	void on_enter();
	void on_input(const ExMessage& msg);

public:
	const Vector2D& get_position()const;
	int  getJitterRadius();
	Timer& getTimer();
	int getJitterTime();

	void setPosition(int x, int y);
	void setJitter_TimeAndR(int time,int r);
	void setJitterStart(bool flag);//������ʼ

private:
	bool isJitter = false;	//�Ƿ񶶶�
	int JitterTime = 0;		//����ʱ��
	int JitterRadius=0;		//�����뾶
	Vector2D cur_pos;		//��ǰ����
	Timer timer;			//��ʱ��
};

