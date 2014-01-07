#include "map.h"

int isPassable(struct tiles *tile)
{
    return tile->passability;
}

int isVisible(struct tiles *tile)
{
    return tile->visibility;
}
