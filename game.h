#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "player.h"
#include "mapgen.h"
#include "init.h"
#include "misc.h"

#define BLACK_COLOR 0,0,0
#define RED_COLOR 255,0,0
#define BLUE_COLOR 0,0,255
#define GREEN_COLOR 0,255,0
#define WHITE_COLOR 255,255,255
#define GREY_COLOR 100,100,100
#define MASK_COLOR 255,0,255

#define LOGO_FONT_SIZE_LARGE 250
#define MENU_FONT_SIZE_LARGE 50

struct options OPTIONS;

struct options
{
    int fullscreen,width,height,bpp;
};


void onInit();
int onMainMenu();
int onLoop();
void drawScene();
int onOptionsMenu();
void loadOptions();
void saveOptions(struct options *opt);

#endif // GAME_H_INCLUDED
