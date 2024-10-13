#pragma once
#include "Player.h"
class Sunflower :
    public Player
{
public:
    Sunflower(PlayerId id);
    ~Sunflower();

    void on_update(int delta_time)override;
    void on_draw(const Camera& camera)override;
    void on_input(const ExMessage& msg)override;

    virtual std::vector<Player::BulletType> collision_bullet(const Player& another);
    virtual void on_attack();
private:
    //¥Û’–
    Bullet* sunBullet_ex = nullptr;
    float sunBullet_ex_length = 200;

};

