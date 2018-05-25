#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "window.h"
#include "tools.h"

class Player
{
    public:
        Player(const std::string &sprite_path);
        virtual ~Player();

        void draw() const;
        void pollEvents(SDL_Event &event);

    protected:

    private:
        int _w = 240;
        int _h = 240;
        int _x = 100;
        int _y = 100;
        bool _waitingForAction = true;
        SDL_Texture *_texture = nullptr;
};

#endif // PLAYER_H
