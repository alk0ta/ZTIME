#include "player.h"

void generateTables()
{
    int i,j;
    double angle;
    for(i=0;i<8;i++)
    {
        for(j=0;j<12;j++)
        {
            angle=(j*5+i*45+15)*PI/180;
            cosinus[i][j]=cos(angle);
            sinus[i][j]=sin(angle);
        }
    }
}

void BLA(int x1, int y1, int x2, int y2, struct tiles **sector)
{
    int deltax=x2-x1;
    int deltay=y2-y1;
    int signx=x1<x2?1:-1;
    int signy=y1<y2?1:-1;
    int error=deltax-deltay;
    sector[y2*SECTOR_SIDE_SIZE+x2]->visibility=VISIBLE;
    while(x1!=x2||y1!=y2)
    {
        if(!sector[y1*SECTOR_SIDE_SIZE+x1]->visibility)
            sector[y1*SECTOR_SIDE_SIZE+x1]->visibility=VISIBLE;
        if(!sector[y1*SECTOR_SIDE_SIZE+x1]->opaque)
            return;
        int error2=error*2;
        if(error2>deltay)
        {
            error-=deltay;
            x1+=signx;
        }
        if(error2<deltax)
        {
            error+=deltax;
            y2+=signy;
        }

    }
}

int getEndX(int x, int sight, int angle, direction dir)
{
    return round(x+sight*cosinus[dir][angle]);
}

int getEndY(int y, int sight, int angle, direction dir)
{
    return round(y+sight*sinus[dir][angle]);
}

void lookAt(direction dir,struct _character *character,struct tiles *sector[])
{
    int i, endx, endy;
    for(i=0;i<12;i++)
    {
        endx=getEndX(character->pos_x,character->sight,i,character->dir);
        endy=getEndY(character->pos_y,character->sight,i,character->dir);
        BLA(character->pos_x,character->pos_y,endx,endy,*sector);
    }
}

void moveCharacter(direction dir, struct _character *character)
{
    switch (dir)
    {
        case N:
            if (character->dir!=N)
            {
                    character->dir=N;
            }
            else
                character->pos_y--;
            break;
        case NE:
            if (character->dir!=NE)
                character->dir=NE;
            else
            {
                character->pos_x++;
                character->pos_y--;
            }
            break;
        case E:
            if (character->dir!=E)
                character->dir=E;
            else
                character->pos_x++;
            break;
        case SE:
            if (character->dir!=SE)
                character->dir=SE;
            else
            {
                character->pos_x++;
                character->pos_y++;
            }
            break;
        case S:
            if (character->dir!=S)
                character->dir=S;
            else
                character->pos_y++;
            break;
        case SW:
            if (character->dir!=SW)
                character->dir=SW;
            else
            {
                character->pos_x--;
                character->pos_y++;
            }
            break;
        case W:
            if (character->dir!=W)
                character->dir=W;
            else
                character->pos_x--;
        case NW:
            if (character->dir!=NW)
                character->dir=NW;
            else
            {
                character->pos_x--;
                character->pos_y--;
            }
            break;
    }
}
