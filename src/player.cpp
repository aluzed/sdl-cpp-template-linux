#include "player.h"
#include "SDL2/SDL_image.h"

Player::Player(const std::string &sprite_path)
{
    auto surface = IMG_Load(sprite_path.c_str());
    if(!surface)
    {
        std::cerr << "Fail to load the surface" << std::endl;
    }

    _texture = SDL_CreateTextureFromSurface(Window::renderer, surface);

    if(!_texture)
    {
        std::cerr << "Fail to create texture" << std::endl;
    }

    SDL_FreeSurface(surface);
}

Player::~Player()
{
    SDL_DestroyTexture(_texture);
}

void Player::draw() const
{
    SDL_Rect rect = { _x, _y, _w, _h };

    if(_texture)
    {
        SDL_RenderCopy(Window::renderer, _texture, nullptr, &rect);
    }
    else
    {
        SDL_SetRenderDrawColor(Window::renderer, 200, 0, 200, 255);
        SDL_RenderFillRect(Window::renderer, &rect);
    }
}


void Player::pollEvents(SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
                std::cout << "key up pressed" << std::endl;
                _y -= 5;
                break;
            case SDLK_DOWN:
                std::cout << "key down pressed" << std::endl;
                _y += 5;
                break;
            case SDLK_LEFT:
                _x -= 5;
                std::cout << "key left pressed" << std::endl;
                break;
            case SDLK_RIGHT:
                _x += 5;
                std::cout << "key right pressed" << std::endl;
                break;
            // case SDLK_RIGHT+SDLK_UP:
               // _x += 5;
                //_y -= 5;
                //std::cout << "key diag up \n";
                //break;
        }
    }
}
