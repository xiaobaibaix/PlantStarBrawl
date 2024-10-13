#pragma once
#include "Player.h"
class Peashooter :
    public Player
{
public:
    Peashooter(PlayerId id);
    ~Peashooter();

    virtual void on_attack();

    void on_update(int delta_time)override;
    void on_draw(const Camera& camera)override;
    void on_input(const ExMessage& msg)override;

};

