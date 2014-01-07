#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include "map.h"
#include <math.h>
#include <stdlib.h>

typedef struct stack
{
    int value;
    struct stack *next;
} s_stack, s_node;

int is_empty(s_stack **top);
int push(s_stack **top, int value);
void pop(s_stack **top);
int peek(s_stack **top);
void clear(s_stack **top);
int randRange(int min, int max);
int _round(double x);
void itoa(int n,char str[]);

#endif // MISC_H_INCLUDED
