#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    int nbytes = 512;
    unsigned char temp[nbytes];
    char filename[8];
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *f = fopen(argv[1],"r");
    if (f == NULL)
    {
        printf("File can not be opened\n");
        return 1;
    }
    FILE *storage = NULL;
    for (int i = 0; fread(temp, nbytes, 1, f) == 1; i++)
    {
        
        if (temp[0] == 0xff && temp[1] == 0xd8 && temp[2] == 0xff && (temp[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", i);
            storage = fopen(filename,"w");
            fwrite(&temp, 512, 1, storage);
            fclose(storage);
        }
    }

    fclose(f);
    fclose(storage);
}