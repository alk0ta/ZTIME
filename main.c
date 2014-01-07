#include "init.h"
#include "game.h"
#include <stdio.h>

int main()
{
    onInit();
    onMainMenu();
    onLoop();
    return 1;
    atexit(SDL_Quit);
}
