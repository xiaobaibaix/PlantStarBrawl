#pragma once
#include "Bullet.h"
class PeaBullet :
    public Bullet
{
public:
    friend class Player;
    PeaBullet();
    ~PeaBullet();

    virtual bool check_collide(Point pos, Rect rect);//�����ײ
    virtual bool check_collide(Rect rect1, Rect rect2);//�����ײ

    virtual void on_update(int delta_time)override;
    virtual void on_draw(const Camera& camera)override;

private:
    Animation animation;
    IMAGE* img = nullptr;
};

