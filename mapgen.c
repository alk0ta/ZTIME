#include "mapgen.h"

//int to_neighbours[8]={-SIDE_SIZE,-SIDE_SIZE+1,1,SIDE_SIZE+1,SIDE_SIZE,SIDE_SIZE-1,-1};

float noise(int x, int y)
{
    int n=x+y*57;
    n=(n<<13)^n;
    return (1.0f-((n*(n*n*15731+789221)+1376312589)&0x7fffffff)/1073741824.0f);
}

float interpolate(float a, float b, float x)
{
    return a*(1-x)+b*x;
}

float _interpolate(float a, float b, float x)
{
    float ft=x*3.1415927;
	float f=(1-cos(ft))*0.5;
	return a*(1-f)+b*f;
}

float smoothNoise(float x, float y)
{
    float corners=(noise(x-1,y-1)+noise(x+1,y-1)+noise(x-1,y+1)+noise(x+1,y+1))/16;
    float sides=(noise(x-1,y)+noise(x+1,y)+noise(x,y-1)+noise(x,y+1))/8;
    float center = noise(x,y)/4;
    return corners+sides+center;
}

float interpolatedNoise(float x, float y)
{
    int int_x=(int)x;
    float fract_x=x-int_x;
    int int_y=(int)y;
    float fract_y=y-int_y;
    float v1=smoothNoise(int_x, int_y);
    float v2=smoothNoise(int_x+1, int_y);
    float v3=smoothNoise(int_x, int_y+1);
    float v4=smoothNoise(int_x+1,int_y+1);
    float i1=interpolate(v1, v2, fract_x);
    float i2=interpolate(v3, v4, fract_x);
    return interpolate(i1, i2, fract_y);
}

int perlinNoise(float x,float y,float factor)
{
   float total=1;
   float persistence=0.2f;
   float frequency=0.1f;
   float amplitude=0.01;
   x=x+factor;
   y=y+factor;
   int i;
   for(i=0; i<2; i++)
   {
       total+=interpolatedNoise(x*frequency, y*frequency)*amplitude;
       amplitude*=persistence;
       frequency*=2;
    }
    total=fabsf(total);
    return (int)(total*2.0f);
}

void generateNoise(int *pNoise)
{
    int i,j;
    srand(time(NULL));
    float fac=rand()*0.025;
    for(i=0 ;i<MAP_SIDE_SIZE;i++)
    {
        for(j=0 ;j<MAP_SIDE_SIZE;j++)
        {
            pNoise[i*MAP_SIDE_SIZE+j]=perlinNoise(i,j,fac);
        }
    }
}

int generateZones(int *noises, int *noisesBuf)
{
    int to_neighbours[8]={-MAP_SIDE_SIZE,-MAP_SIDE_SIZE+1,1,MAP_SIDE_SIZE+1,MAP_SIDE_SIZE,MAP_SIDE_SIZE-1,-1};
    int i,j,current_pos,_noise,type_zone;
    int visited=256;
    int pos_neighbour;
    s_stack *_stack=NULL;
    for(i=0;i<MAP_SIZE;i++)
    {
        if(noisesBuf[i]==visited)
            continue;
        if(!push(&_stack,i))
            return 0;
        type_zone=randRange(FOREST,CITY);
        _noise=noises[i];
        while(!is_empty(&_stack))
        {
            current_pos=peek(&_stack);
            pop(&_stack);
            for(j=0;j<8;j++)
            {
                pos_neighbour=current_pos+to_neighbours[j];
                if(((pos_neighbour)<MAP_SIZE)&&(pos_neighbour>=0))
                {
                    if(noisesBuf[pos_neighbour]==_noise)
                    {
                        if(!push(&_stack,pos_neighbour))
                            return 0;
                        noises[pos_neighbour]=type_zone;
                        noisesBuf[pos_neighbour]=visited;
                    }
                }

            }
        }
    }
    clear(&_stack);
    return 1;
}

struct tiles* FBM(zone_type ztype,int depth)
{
    int dposx,dposy, pos,count,ind;
    struct tiles sector[SECTOR_SIZE],tile,*_tiles;
    tile_type bg;
    pos=randRange(0,SECTOR_SIZE);
    count=0;
    if(ztype==FOREST)
    {
        bg=GRASS;
        struct tiles tile={bg,100,NOT_VISIBLE,FOR_ALL};
        struct tiles _tiles[]={SHRUB,YOUNG_TREE,TREE};
        ind=2;

    }
    if(ztype==FIELDS)
    {
        bg=GRASS;
        struct tiles tile={bg,100,NOT_VISIBLE,FOR_ALL};
        struct tiles _tiles[]={SHRUB};
        ind=0;
    }
    if(ztype==LAKES)
    {
        struct tiles tile={WATER,500,NOT_VISIBLE,FOR_HUMAN};
    }
    while(count!=SECTOR_SIZE)
    {
        sector[count]=tile;
        count++;
    }
    count=0;
    while(count!=depth)
    {   dposx=randRange(-5,5);
        dposy=randRange(-5*SECTOR_SIDE_SIZE,5*SECTOR_SIDE_SIZE);
        if(((pos*dposy+dposx)>SECTOR_SIZE)||((pos*dposy+dposy)<0))
        {
            pos=randRange(0,SECTOR_SIZE);
            continue;
        }
        pos=pos*dposy+dposx;
        sector[pos]=_tiles[randRange(0,ind)];
        sector[pos].bgtile=bg;
        count++;
    }
    return sector;
}

void midPoint(tile_type stype1, tile_type ttype2,s_stack s)
{

}


int generateSector(struct tiles *Map, int *zones, int x, int y)
{
    int to_neighbours[8]={MAP_SIDE_SIZE,-MAP_SIDE_SIZE,1,-1,MAP_SIDE_SIZE+1,MAP_SIDE_SIZE-1,-MAP_SIDE_SIZE+1,-MAP_SIDE_SIZE-1};
    int i,neighbour,zone,num_neighbours=0;
    s_stack s;
    zone=zones[y*MAP_SIDE_SIZE+x];
    for(i=0;i<8;i++)
    {
        neighbour=y*MAP_SIDE_SIZE+x+to_neighbours[i];
        if((neighbour<MAP_SIZE)&&(neighbour>0))
        {
            if((zones[neighbour]!=zone))
            {
                num_neighbours++;
                push(&s,i);
            }

        }
    }
    if(!num_neighbours)
    {
        if(zone==FOREST)
        {
            FBM(FOREST,700);
        }
        if(zone==FIELDS)
        {
            FBM(FIELDS,10);
        }
        if(zone==LAKES)
        {
            FBM(LAKES,0);
        }
    }
    if(num_neighbours==1)
    {
        if(peek(&s)>3)
        {
            if(zone==FOREST)
            {
                FBM(FOREST,700);
            }
            if(zone==FIELDS)
            {
                FBM(FIELDS,10);
            }
        }
        if(peek(&s)<2)
        {

        }
    }
    if(num_neighbours>1)
    {

    }
    return 1;
}

void generateMap()
{
    struct tiles Map[9][SECTOR_SIZE];
    int sector;
    for(sector=0;sector<9;sector++)
    {

    }
}
