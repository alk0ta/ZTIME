#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "map.h"
#include "mapgen.h"
#include "misc.h"
#include <math.h>

#define PI 3.1415926535

double sinus[7][11], cosinus[7][11];

typedef enum
{
    NE=0,
    N,
    NW,
    W,
    SW,
    S,
    SE,
    E
} direction;

struct _character
{
        char name[20];
        char id;
        int color;
        int pos_x;
        int pos_y;
        direction dir;
        int sight;

};

void moveCharacter(direction dir, struct _character *character);
void lookAt(direction dir, struct _character *character, struct tiles *sector[]);
int getEndX(int x, int sight, int angle, direction dir);
int getEndY(int y, int sight, int angle, direction dir);
void BLA(int x1,int y1,int x2, int y2, struct tiles *sector[]);
void generateTables();


#endif // PLAYER_H_INCLUDED
