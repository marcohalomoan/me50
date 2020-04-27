#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float c = get_float("Change owed: ");
    while (c < 0)
    {
        c = get_float("Change owed: ");
    }
    int cents = round(c * 100);
    int i = 25, j = 10, k = 5, l = 1, n = 0;
    while (cents >= i)
    {
        cents -= i;
        n++;
    }
    while (cents >= j)
    {
        cents -= j;
        n++;
    }
    while (cents >= k)
    {
        cents -= k;
        n++;
    }
    while (cents >= l)
    {
        cents -= l;
        n++;
    }
    printf("%i\n", n);
}
