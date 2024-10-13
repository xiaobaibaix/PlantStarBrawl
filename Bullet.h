#pragma once
#include "Vector2D.h"
#include <functional>
#include "Animation.h"
#include "Camera.h"
#include "Player.h"
#include "SceneManager.h"
#include "common.h"

extern bool is_debug;
extern SceneManager scene_manager;


class Bullet
{
public:
	friend class Player;
	Bullet()=default;
	virtual~Bullet();
	//λ��
	void setPos(const Point& point);
	const Point& getPos();
	//�˺�
	void setDamage(int damamge);
	int getDamage();
	//�ӵ���С	
	void setSize(const Vector2D& size);
	const Vector2D& getSize();
	//�ٶ�
	void setSpeed(const Vector2D& speed);
	const Vector2D& getSpeed();
	//����id
	void setTargetId(Player::PlayerId target);
	Player::PlayerId getTargetId();
	//�ӵ���Ч���
	void setValid(bool valid);
	bool getValid();
	//�ӵ�ɾ�����
	void setRemove(bool remove);
	bool getRemove();
	//id
	void setId(int id);
	int getId();
	//�ص�����
	void setCallback(std::function<void()> callback);

	void reset();//����
	void fire(Point pos, int dir);//����

	virtual void on_collide();//��ײ����

	virtual bool check_collide(Point pos, Rect rect);//�����ײ
	virtual bool check_collide(Rect rect1, Rect rect2);//�����ײ

	virtual void on_update(int delta_time)=0;
	virtual void on_draw(const Camera& camera);

	void check_out_screen();//������

protected:
	int id = 0;//�ӵ�id
	static int damage;//�˺�
	static int energy;//�˺�

	Point pos = {0};//λ��
	Vector2D size = {0};//�ӵ���С
	Vector2D size_explode = { 0 };//��ը��Χ
	Vector2D speed = {0};//�ӵ��ٶ�

	bool is_valid = true;//�Ƿ���Ч
	bool is_remove = false;//�Ƿ�ɾ��

	Player::PlayerId target_id=Player::PlayerId::invalid;//�����Ŀ�����

	std::function<void()> callback;


};

