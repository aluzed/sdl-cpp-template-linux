#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "window.h"

class Player : public Window
{
    public:
        Player(const Window &window);
        virtual ~Player();

        void draw() const;
        void pollEvents();

    protected:

    private:
        int _w = 120;
        int _h = 120;
        int _x = 100;
        int _y = 100;
        bool _waitingForAction = true;
};

#endif // PLAYER_H
