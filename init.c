#include "init.h"

int SDLinit()
{
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO)<0)
    {
        printf("Unable to init SDL: %s\n",SDL_GetError());
        return 0;
    }
    screen=SDL_SetVideoMode(OPTIONS.width,OPTIONS.height,OPTIONS.bpp,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (screen==NULL)
    {
        printf("Unable to set %dx%d video: %s\n", OPTIONS.width,OPTIONS.height,SDL_GetError());
        return -1;
    }
    if(OPTIONS.fullscreen)
    {
        if(!SDL_WM_ToggleFullScreen(screen))
        {
            printf("Unable to set fullscreen mode:%s",SDL_GetError());
            return 0;

        }
    }
    return 1;
}

SDL_Surface *loadImage(char *filename)
{
    SDL_Surface *loadedimage=NULL;
    SDL_Surface *image=NULL;
    loadedimage=IMG_Load(filename);
    if(loadedimage!=NULL)
    {
        image=SDL_DisplayFormat(loadedimage);
        SDL_FreeSurface(loadedimage);
    }
    return image;
}
