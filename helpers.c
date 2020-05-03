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
    int tempblue[height][width], tempgreen[height][width], tempred[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempblue[i][j] = image[i][j].rgbtBlue;
            tempgreen[i][j] = image[i][j].rgbtGreen;
            tempred[i][j] = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tempblue[i][width - j - 1];
            image[i][j].rgbtGreen = tempgreen[i][width - j - 1];
            image[i][j].rgbtRed = tempred[i][width - j - 1];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avgb, avgg, avgr;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue) / 4;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen) / 4;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed) / 4;
            }
            else if (i == 0 && j == width - 1)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue) / 4;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen) / 4;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed) / 4;
            }
            else if (i == height - 1 && j == 0)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i - 1][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue) / 4;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i - 1][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen) / 4;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i - 1][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i - 1][j + 1].rgbtRed) / 4;
            }
            else if (i == height - 1 && j == width - 1)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i - 1][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue) / 4;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i - 1][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen) / 4;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i - 1][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j - 1].rgbtRed) / 4;
            }
            else if (i == 0 && j != 0 && j != width - 1)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue) / 6;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen) / 6;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j + 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed) / 6;
            }
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue) / 6;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen) / 6;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j].rgbtRed + (float)image[i - 1][j + 1].rgbtRed + (float)image[i - 1][j - 1].rgbtRed) / 6;
            }
            else if (j == 0 && i != 0 && i != height - 1)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue) / 6;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen) / 6;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i - 1][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i - 1][j + 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed) / 6;
            }
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue) / 6;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen) / 6;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i - 1][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i - 1][j - 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed) / 6;
            }
            else
            {
                avgb = ((float)image[i][j].rgbtBlue + (float)image[i + 1][j].rgbtBlue + (float)image[i - 1][j].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue) / 9;
                avgg = ((float)image[i][j].rgbtGreen + (float)image[i + 1][j].rgbtGreen + (float)image[i - 1][j].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen) / 9;
                avgr = ((float)image[i][j].rgbtRed + (float)image[i + 1][j].rgbtRed + (float)image[i - 1][j].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i][j - 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed + (float)image[i - 1][j + 1].rgbtRed + (float)image[i - 1][j - 1].rgbtRed) / 9;
            }
            image[i][j].rgbtBlue = round(avgb) + 20;
            image[i][j].rgbtGreen = round(avgg) + 20;
            image[i][j].rgbtRed = round(avgr) + 18;
        }
    }
    return;
}
