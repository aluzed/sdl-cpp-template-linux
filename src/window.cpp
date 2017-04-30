#include "window.h"

Window::Window(const std::string &title, int width, int height) :
    _title(title), _width(width), _height(height)
{
    _closed = !init();
}

Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Window::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL init error " << std::endl;
        return 0;
    }

    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_RESIZABLE);

    if(_window == nullptr)
    {
        std::cerr << "Failed to create window" << std::endl;
        return 0;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if(_renderer == nullptr)
    {
        std::cerr << "Failed to render window" << std::endl;
        return 0;
    }

    return true;
}

void Window::pollEvents()
{
    SDL_Event event;

    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT: _closed = true; break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        std::cout << "key up pressed" << std::endl;
                        break;
                }
                break;
            /*
            Mouse case for example
            case SDL_MOUSEMOTION:
                std::cout << "moving the mouse (" << event.motion.x << ", " << event.motion.y << ")" << std::endl";
                break;
            */
            default: break;
        }
    }
}

void Window::clear() const
{

    //Present first to display sprites before rendering background
    SDL_RenderPresent(_renderer);

    //Set the color to the render - R G B A
    SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);

    SDL_RenderClear(_renderer);
}

GameContext Window::getGameContext()
{
    return _gameContext;
}

void Window::setGameContext(GameContext gc)
{
    _gameContext = gc;
}
