#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

// inroduce 8-bit data type
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // set the number of bytes in one block of the RAW file
    int nbytes = 512;
    // create an array of bytes to store recovered bytes
    BYTE bytes[nbytes];
    // create an array for file names
    char filename[8];
    // make sure it is single argument command
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // open the file
    FILE *f = fopen(argv[1], "r");
    // make sure it works
    if (f == NULL)
    {
        printf("File can not be opened\n");
        return 1;
    }
    // create a file to store the recovered JPEGs
    FILE *storage = NULL;
    bool check = false;
    for (int i = 0; fread(bytes, nbytes, 1, f) == 1; i++)
    {
        // when it finds "signature"
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            // if it is not the first JPEG found
            if (check == true)
            {
                fclose(storage);
            }
            else
            {
                check = true;
            }
            // print the filename to string
            sprintf(filename, "%03i.jpg", i);
            // open new file with that the previous filename
            storage = fopen(filename, "w");
        }
        else
        {
            // make sure it only incremented when a JPEG found
            i--;
        }
        if (check == true)
        {
            // copying the bytes from array of bytes to new file
            fwrite(bytes, 512, 1, storage);
        }
    }
    // close everything
    fclose(f);
    fclose(storage);
}