#pragma once
#include "SunBullet.h"
#include "Animation.h"

class SunBulletEx :
    public SunBullet
{
public:
    friend class Player;

    SunBulletEx();
    ~SunBulletEx();

    virtual bool check_collide(Point pos, Rect rect);//¼ì²éÅö×²
    virtual bool check_collide(Rect rect1, Rect rect2);//¼ì²éÅö×²

    virtual void on_update(int delta_time)override;
    virtual void on_draw(const Camera& camera)override;

    void setTextPos(Point pos);
    void setTextExist(bool flag);
    Animation& getAniamtionText();

private:
    Point text_pos = { 0 };
    bool is_exist_text = false;//ÊÇ·ñ´æÔÚ

    Animation animation_sun_text;
};

