#include "window.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

SDL_Renderer* Window::renderer = nullptr;

Window::Window(const std::string &title, int width, int height) :
    _title(title), _width(width), _height(height)
{
    _closed = !init();
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Window::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL init error" << std::endl;
        return false;
    }

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Error, while intitializing IMG PNG" << std::endl;
        return false;
    }

    if(TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize SDL_TTF" << std::endl;
        return false;
    }

    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_RESIZABLE);

    if(_window == nullptr)
    {
        std::cerr << "Failed to create window" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        std::cerr << "Failed to render window" << std::endl;
        return false;
    }

    return true;
}

void Window::pollEvents(SDL_Event &event)
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
            std::cout << "moving the mouse (" << event.motion.x << ", " << event.motion.y << ")\n";
            break;
        */
        default: break;
    }
}

void Window::clear() const
{

    //Present first to display sprites before rendering background
    SDL_RenderPresent(renderer);

    //Set the color to the render - R G B A
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);

    SDL_RenderClear(renderer);
}

GameContext Window::getGameContext()
{
    return _gameContext;
}

void Window::setGameContext(GameContext gc)
{
    _gameContext = gc;
}
