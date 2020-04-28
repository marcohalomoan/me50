#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int n_arg, string key[])
{
    if (n_arg != 2)
    {
        printf("Expected a value of key\n");
        return 1;
    }
    for (int i = 0; i < strlen(key[1]); i++)
    {
        if (key[1][i] < 48 || key[1][i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int k = atoi(key[1]);
    string text = get_string("plaintext : ");
    for (int j = 0; j < strlen(text); j++)
    {
        if (text[j] >= 65 && text[j] <= 90)
        {
            text[j] = (text[j] + k - 65) % 26;
            text[j] += 65;
        }
        else if (text[j] >= 97 && text[j] <= 122)
        {
            text[j] = (text[j] + k - 97) % 26;
            text[j] += 97;
        }
    }
    printf("ciphertext: %s\n",text);
}