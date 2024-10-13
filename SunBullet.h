#pragma once
#include "Bullet.h"
#include "Animation.h"

class SunBullet :
    public Bullet
{
public:
    friend class Player;

    SunBullet();
    virtual~SunBullet();

    virtual bool check_collide(Point pos, Rect rect);//�����ײ
    virtual bool check_collide(Rect rect1, Rect rect2);//�����ײ

    virtual void on_update(int delta_time)override;
    virtual void on_draw(const Camera& camera)override;

protected:

    Animation animation_sun[2];

    float a = 0;//��׹���ٶ�
};

