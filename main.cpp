#include <iostream>
#include "window.h"
#include "player.h"
#include "text.h"
#define WIN_WIDTH 640
#define WIN_HEIGHT 480


// int main(int argc, char** argv)
// {
//     Window window("SDL Test", WIN_WIDTH, WIN_HEIGHT);
//     Player player1(window);
//
//     while(!window.isClosed())
//     {
//         player1.pollEvents();
//         player1.draw();
//         window.pollEvents();
//         window.clear();
//     }
//
//     return 0;
// }

void pollEvents(Window &window, Player &player)
{
    SDL_Event event;

    if(SDL_PollEvent(&event))
    {
        player.pollEvents(event);
        window.pollEvents(event);
    }
}


int main(int argc, char** argv)
{
    Window window("SDL Test", WIN_WIDTH, WIN_HEIGHT);
    Player player1("res/cat.png");
    Text text(Window::renderer, "res/fonts/arial.ttf", 30, "Render test", { 255, 255, 255, 255 });

    while(!window.isClosed())
    {
        pollEvents(window, player1);
        player1.draw();
        text.display(20, 20, Window::renderer);
        window.clear();
    }

    return 0;
}
