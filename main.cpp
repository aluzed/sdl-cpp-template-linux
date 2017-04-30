#include <iostream>
#include "window.h"
#include "player.h"
#define WIN_WIDTH 640
#define WIN_HEIGHT 480


int main(int argc, char** argv)
{
    Window window("SDL Test", WIN_WIDTH, WIN_HEIGHT);
    Player player1(window);

    while(!window.isClosed())
    {
        player1.pollEvents();
        player1.draw();
        window.pollEvents();
        window.clear();
    }

    return 0;
}
