#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int n = get_int("Height = ");
    if (n >= 1 && n <= 8)
    {
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k <= n-i-1 ; k++)
            {
                printf(" ");
            }
            for (int j = 0; j <= i; j++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
    else
    {
        n = get_int("Height = ");
    }
}
