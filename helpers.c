#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float newblue, newgreen, newred;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newblue = 0.272 * (float)image[i][j].rgbtRed + 0.534 * (float)image[i][j].rgbtGreen + 0.131 * (float)image[i][j].rgbtBlue;
            newgreen = 0.349 * (float)image[i][j].rgbtRed + 0.686 * (float)image[i][j].rgbtGreen + 0.168 * (float)image[i][j].rgbtBlue;
            newred = 0.393 * (float)image[i][j].rgbtRed + 0.769 * (float)image[i][j].rgbtGreen + 0.189 * (float)image[i][j].rgbtBlue;
            if (round(newblue) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(newblue);
            }
            if (round(newgreen) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(newgreen);
            }
            if (round(newred) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(newred);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
