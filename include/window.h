#pragma once

#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <iostream>
#include "tools.h"
#include "SDL2/SDL.h"

enum GameContext { GAME, MENU, CUTSCENE };

class Window
{
    public:
        Window(const std::string &title, int width, int height);
        virtual ~Window();

        void pollEvents(SDL_Event &event);
        void clear() const;

        inline bool isClosed() const { return _closed; }
        GameContext getGameContext();
        void setGameContext(GameContext gc);
        int getScreenWidth() const { return _width; }
        int getScreenHeight() const { return _height; }

        static SDL_Renderer* renderer;

    private:
        bool init();

        std::string _title;
        int _width = 640;
        int _height = 480;

        bool _closed = false;

        SDL_Window* _window = nullptr;
        GameContext _gameContext = GameContext::GAME;
};

#endif // WINDOW_H
