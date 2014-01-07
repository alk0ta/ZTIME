#include "misc.h"

int is_empty(s_stack **top)
{
    return *top==NULL;
}

int push(s_stack **top,int value)
{
    s_node *snode=(s_node *)malloc(sizeof(s_node));
    if(snode==NULL)
        return 0;
    snode->value=value;
    snode->next=NULL;
    if(!is_empty(top))
        snode->next=(*top);
    (*top)=snode;
    return 1;
}

void pop(s_stack **top)
{
    s_node *snode;
    if(!is_empty(top))
    {
        snode=*top;
        (*top)=(*top)->next;
        free(snode);
        snode = NULL;
    }
}

int peek(s_stack **top)
{
    if(!is_empty(top))
        return (*top)->value;
    else
        return NULL;
}

void clear(s_stack **top)
{
    while(!is_empty(top))
        pop(top);
}


int randRange(int min,int max)
{
    return rand()/(RAND_MAX+1.0)*(max-min+1)+min;

}

int _round(double x)
{
    double y;
    if (modf(x,&y)>0.5)
        return (int)(y+1);
    else
        return (int)y;
}

void itoa(int n, char str[])
 {
     int i, sign;
     if ((sign = n) < 0)
         n = -n;
     i = 0;
     do {
         str[i++] = n % 10 + '0';
     } while ((n /= 10) > 0);
     if (sign < 0)
         str[i++] = '-';
     str[i] = '\0';
     reverse(str);
 }

void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
