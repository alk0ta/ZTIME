#ifndef MAPGEN_H_INCLUDED
#define MAPGEN_H_INCLUDED

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "map.h"
#include "misc.h"

#define MAP_SIZE 2500
#define MAP_SIDE_SIZE 50
#define SECTOR_SIDE_SIZE 30
#define SECTOR_SIZE 900

typedef enum _zone_type
{
    FOREST=0,
    FIELDS,
    MOUNTS,
    LAKES,
    CITY
} zone_type;

float noise(int x, int y);
float interpolate(float a, float b, float x);
float smoothNoise(float x, float y);
float interpolatedNoise(float x, float y);
int perlinNoise(float x, float y, float factor);
void generateNoise(int *pNoise);
int generateZones(int *noises,int *noisesBuf);
struct tiles* FBM(zone_type ztype,int depth);
void midPoint(tile_type ttype1, tile_type ttype2,s_stack s);
int generateSector(struct tiles *Map,int *zones,int x, int y);

#endif // MAPGEN_H_INCLUDED
