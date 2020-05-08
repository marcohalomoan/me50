#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int nbytes = 512;
    BYTE bytes[nbytes];
    char filename[8];
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("File can not be opened\n");
        return 1;
    }
    FILE *storage = NULL;
    bool check = false;
    for (int i = 0; fread(bytes, nbytes, 1, f) == 1; i++)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (check == true)
            {
                fclose(storage);
            }
            else
            {
                check = true;
            }
            sprintf(filename, "%03i.jpg", i);
            storage = fopen(filename, "w");
        }
        else
        {
            i--;
        }
        if (check == true)
        {
            fwrite(&bytes, 512, 1, storage);
        }
    }

    fclose(f);
    fclose(storage);
}