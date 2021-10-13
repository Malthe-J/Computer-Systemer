#include<stdio.h>
#include <stdbool.h>
int main()
{
    int x = 3;
    int y = 2;
 
    
    printf("x<<3 = %d\n", x<<3);

    if (x^6)
    {
        return false;
    }

    else {
        return true;
    }

    if (x <= 0)
    {
        return true;
    }

    if (x != y)
    {
        return true;
    }
    
}