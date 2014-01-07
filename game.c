#include "game.h"


void onInit()
{
    loadOptions();
    SDLinit(&OPTIONS);
//    generateTables();
}

void drawScene()
{

}

int onLoop()
{
    int running=TRUE;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type==SDL_QUIT)
                running=FALSE;
            if (event.type==SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        break;
                    case SDLK_RIGHT:
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_ESCAPE:
                        running=FALSE;
                        break;
                }
            }
        }
    }
    return 1;
}

int onMainMenu()
{
    int running=TRUE;
    int i;
    int ind=0;
    SDL_Event event;
    SDL_Surface *logo_textsurf=NULL;
    SDL_Surface *menu_textsurf=NULL;
    SDL_Color fcolor1={RED_COLOR};
    SDL_Color fcolor2={WHITE_COLOR};
    SDL_Rect logo_textpos;
    SDL_Rect menu_textpos;
    char menu[5][10]={"New Game","Load Game","Options","Credits","Exit"};
    if(TTF_Init()==-1)
    {
        printf("Unable to init TTF:%s\n",TTF_GetError());
        return 0;
    }
    TTF_Font *logo_font=NULL;
    TTF_Font *menu_font=NULL;
    logo_font=TTF_OpenFont("./data/gfx/logofont.ttf",LOGO_FONT_SIZE_LARGE);
    menu_font=TTF_OpenFont("./data/gfx/menufont.ttf",MENU_FONT_SIZE_LARGE);
    if(logo_font==NULL|menu_font==NULL)
    {
        printf("Unable to open font:%s\n",TTF_GetError());
        return 0;
    }
    logo_textsurf=TTF_RenderText_Blended(logo_font, "ZTIME", fcolor1);
    if(logo_textsurf==NULL)
    {
        printf("Unable to render text:%s\n",TTF_GetError());
        return 0;
    }
    logo_textpos.x=OPTIONS.width/2-logo_textsurf->w/2;
    logo_textpos.y=10;
    while(running)
    {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(logo_textsurf, NULL, screen, &logo_textpos);
        for(i=0;i<5;i++)
        {
            if(i==ind)
                menu_textsurf=TTF_RenderText_Blended(menu_font,menu[i],fcolor1);
            else
                menu_textsurf=TTF_RenderText_Blended(menu_font,menu[i],fcolor2);
            if(menu_textsurf==NULL)
            {
                printf("Unable to render text:%s\n",TTF_GetError());
                return 0;
            }
            menu_textpos.x=OPTIONS.width/2-menu_textsurf->w/2;
            menu_textpos.y=OPTIONS.height-menu_textsurf->h*(5-i);
            SDL_BlitSurface(menu_textsurf,NULL,screen,&menu_textpos);
        }
        while(SDL_PollEvent(&event))
        {
            if (event.type==SDL_QUIT)
                running=FALSE;
            if (event.type==SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        ind--;
                        if(ind<0)
                            ind=0;
                        break;
                    case SDLK_DOWN:
                        ind++;
                        if(ind>4)
                            ind=4;
                        break;
                    case SDLK_ESCAPE:
                        running=FALSE;
                        exit(1);
                        break;
                    case SDLK_RETURN:
                        if(ind==0)
                        {
                        }
                        if(ind==1)
                        {}
                        if(ind==2)
                        {
                            running=FALSE;
                            onOptionsMenu();
                        }
                        if(ind==3)
                        {}
                        if(ind==4)
                        {
                            running=FALSE;
                            exit(1);
                        }
                        break;
                }
            }
        }
        SDL_Flip(screen);
        SDL_Delay(100);
    }
    SDL_FreeSurface(menu_textsurf);
    SDL_FreeSurface(logo_textsurf);
    TTF_CloseFont(menu_font);
    TTF_CloseFont(logo_font);
    return 1;
}

int onOptionsMenu()
{
    int running=TRUE;;
    int i=0;
    int ind=0;
    int rind=0;
    SDL_Event event;
    SDL_Surface *textsurf,*valuesurf;
    SDL_Rect textpos;
    SDL_Rect valuepos;
    SDL_Color fcolor={WHITE_COLOR};
    SDL_Color select_color={RED_COLOR};
    SDL_Color color;
    struct options opt=OPTIONS;
    char menu[5][12]={"Fullscreen\0","Resolution\0","BitPerPixel\0","Aplly\0","Back\0"};
    int resolution[8][2]={{1024,768},{1152,864},{1280,720},{1280,800},{1280,1024},{1440,900},{1400,1050},{1440,1080}};
    if(TTF_Init()==-1)
    {
        printf("Unable to init TTF:%s\n",TTF_GetError());
        return 0;
    }
    TTF_Font *font=NULL;
    font=TTF_OpenFont("./data/gfx/menufont.ttf",MENU_FONT_SIZE_LARGE);
    if(font==NULL)
    {
        printf("Unable to open font:%s\n",TTF_GetError());
        return 0;
    }
    textpos.x=10;
    while(running)
    {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        textpos.y=10;
        valuepos.y=10;
        for(i=0;i<5;i++)
        {
            textpos.y+=textsurf->h;
            if(i==ind)
                color=select_color;
            else
                color=fcolor;
            textsurf=TTF_RenderText_Blended(font,menu[i],color);
            if(textsurf==NULL)
            {
                printf("Unable to render text:%s\n",TTF_GetError());
                return 0;
            }
            SDL_BlitSurface(textsurf,NULL,screen,&textpos);
            if(i==0)
            {
                if(opt.fullscreen)
                {
                    valuesurf=TTF_RenderText_Blended(font,"<ON",color);
                }
                else
                {
                    valuesurf=TTF_RenderText_Blended(font,"OFF>",color);
                }
            }
            if(i==1)
            {
                char *text=malloc(sizeof(char)*12);
                char *value1=malloc(sizeof(char)*5);
                char *value2=malloc(sizeof(char)*5);
                if(text==NULL|value1==NULL|value2==NULL)
                {
                    printf("No memory error");
                    return 0;
                }
                itoa(resolution[rind][0],value1);
                itoa(resolution[rind][1],value2);
                if(rind>0)
                {
                    strcpy(text,"<\0");
                    strcat(text,value1);
                }
                else
                    strcpy(text,value1);
                    strcat(text,"x");
                    strcat(text,value2);
                    if(rind<7)
                        strcat(text,">");
                valuesurf=TTF_RenderText_Blended(font,text,color);
                free(text);
                free(value1);
                free(value2);
            }
            if(i==2)
            {
                if(opt.bpp==16)
                    valuesurf=TTF_RenderText_Blended(font,"16>",color);
                if(opt.bpp==32)
                    valuesurf=TTF_RenderText_Blended(font,"<32",color);
            }
            if(i<3)
            {
                if(valuesurf==NULL)
                {
                    printf("Unable to render text:%s\n",TTF_GetError());
                    return 0;
                }
                valuepos.x=OPTIONS.width-10-valuesurf->w;
                valuepos.y+=valuesurf->h;
                SDL_BlitSurface(valuesurf,NULL,screen,&valuepos);
            }
        }
        while(SDL_PollEvent(&event))
        {
            if (event.type==SDL_QUIT)
                running=FALSE;
            if (event.type==SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        ind--;
                        if(ind<0)
                            ind=0;
                        break;
                    case SDLK_DOWN:
                        ind++;
                        if(ind>4)
                            ind=4;
                        break;
                    case SDLK_LEFT:
                        if(ind==0)
                        {
                            if(opt.fullscreen)
                                opt.fullscreen=0;
                        }
                        if(ind==1)
                        {
                            rind--;
                            if(rind<0)
                                rind=0;
                            opt.width=resolution[rind][0];
                            opt.height=resolution[rind][1];
                        }
                        if(ind==2)
                        {
                            if(opt.bpp==32)
                                opt.bpp=16;
                        }
                        break;
                    case SDLK_RIGHT:
                        if(ind==0)
                        {
                            if(!opt.fullscreen)
                                opt.fullscreen=1;
                        }
                        if(ind==1)
                        {
                            rind++;
                            if(rind>7)
                                rind=7;
                            opt.width=resolution[rind][0];
                            opt.height=resolution[rind][1];
                        }
                        if(ind==2)
                        {
                            if(opt.bpp==16)
                                opt.bpp=32;
                        }
                        break;
                    case SDLK_ESCAPE:
                        running=FALSE;
                        onMainMenu();
                        break;
                    case SDLK_RETURN:
                        if(ind==3)
                        {
                            running=FALSE;
                            saveOptions(&opt);
                            SDLinit(&OPTIONS);
                            onOptionsMenu();
                        }
                        if(ind==4)
                        {
                            running=FALSE;
                            onMainMenu();
                        }
                        break;
                }
            }
        }
        SDL_Flip(screen);
        SDL_Delay(100);
    }
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_FreeSurface(textsurf);
    TTF_CloseFont(font);
    return 1;
}

void loadOptions()
{
    struct json_object *root,*item;
    struct options opt;
    root=json_object_from_file("./data/gfx/gfxopt.json");
    item=json_object_object_get(root,"width");
    OPTIONS.width=json_object_get_int(item);
    item=json_object_object_get(root,"height");
    OPTIONS.height=json_object_get_int(item);
    item=json_object_object_get(root,"bpp");
    OPTIONS.bpp=json_object_get_int(item);
    item=json_object_object_get(root,"fullscreen");
    OPTIONS.fullscreen=json_object_get_int(item);
    root=NULL;
    item=NULL;
}

void saveOptions(struct options *opt)
{
    json_object *root=json_object_new_object();
    json_object_object_add(root,"width",json_object_new_int(opt->width));
    json_object_object_add(root,"height",json_object_new_int(opt->height));
    json_object_object_add(root,"bpp",json_object_new_int(opt->bpp));
    json_object_object_add(root,"fullscreen",json_object_new_int(opt->fullscreen));
    json_object_to_file("./data/gfx/gfxopt.json",root);
    root=NULL;
    OPTIONS=*opt;
}

