#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(void)
{
    int n, j = 0;
    string text = get_string("Text: ");
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] < 65 || text[i] > 122 || (text[i] < 97 && text[i] > 90))
        {
            j++;
        }
        n = i + 1 - j;
    }
    j = 0;
    printf("%i letter(s)", n);
    for (int i = 0; i <= strlen(text); i++)
    {
        if (text[i] == 32 && (text[i + 1] != 32 || text[i + 1] != 0))
        {
            j++;
        }
    }
    int w = j + 1;
    printf("\n%i word(s)", w);
    j = 0;
    for (int i = 0; i <= strlen(text); i++)
    {
        if (text[i] == 63 || text[i] == 33 || text[i] == 46)
        {
            j++;
        }
    }
    int s = j;
    printf("\n%i sentence(s)", s);
    float L = (float) n / w * 100;
    float S = (float) s / w * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int result = round(index);
    if (result < 1)
    {
        printf("\nBefore Grade 1\n");
    }
    else if (result >= 16)
    {
        printf("\nGrade 16+\n");
    }
    else
    {
        printf("\nGrade %i\n", result);
    }
}