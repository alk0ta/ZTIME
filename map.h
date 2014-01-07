#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

enum passable
{
    NOT_PASSABLE=0,
    FOR_HUMAN,
    FOR_ALL
};

enum visible
{
    NOT_VISIBLE=0,
    NOT_SIGHT,
    VISIBLE
};

typedef enum _tyle_type
{
    DIRT=0,
    GRASS,
    HILL,
    WATER,
    ROAD,
    SHRUB,
    FLOWER,
    STUMP,
    YOUNG_TREE,
    TREE,
    STONE,
    OPEN_DOOR,
    CLOSED_DOOR,
    WINDOW,
    CLOSED_WINDOW,
    OPEN_WINDOW,
    WINDOW_FRAME,
    H_WALL,
    V_WALL,
    NE_CORNER_WALL,
    SE_CORNER_WALL,
    SW_CORNER_WALL,
    NW_CORNER_WALL
} tile_type;

struct tiles
{
    tile_type tile;
    tile_type bgtile;
    int cost;
    enum passable passability;
    enum visible visibility;
    int items[75];
    int opaque;
};

int isPassable(struct tiles *tile);

#endif // MAP_H_INCLUDED
