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

	void set_atlas(Atlas* new_atlas);	//����ͼ��
	void set_loop(bool flag);			//�����Ƿ�ѭ��
	void set_loop(bool flag,int count);	//�����Ƿ�ѭ��
	void set_interval(int ms);			//����֡���
	bool isend();						//�Ƿ񲥷Ž���

	void on_update(int delta);			//��������
	void on_draw(const Camera& camera,int x, int y)const;//��������

private:
	int timer = 0;				//��ʱ��
	int interval = 0;			//֡���
	int idx_frame = 0;			//֡����
	int count = 1;				//���Ŵ���

	bool is_loop = false;		//�Ƿ�ѭ��
	bool is_end = false;		//�Ƿ񲥷Ž���

	Atlas* atlas = nullptr;
};

