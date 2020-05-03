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

    int sumBlue;

    int sumGreen;

    int sumRed;

    float counter;

    //create a temporary table of colors to not alter the calculations

    RGBTRIPLE temp[height][width];



    for (int i = 0; i < width; i++)

    {

        for (int j = 0; j < height; j++)

        {

            sumBlue = 0;

            sumGreen = 0;

            sumRed = 0;

            counter = 0.00;



            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic

            for (int k = -1; k < 2; k++)

            {

                if (j + k < 0 || j + k > height - 1)

                {

                    continue;

                }



                for (int h = -1; h < 2; h++)

                {

                    if (i + h < 0 || i + h > width - 1)

                    {

                        continue;

                    }



                    sumBlue += image[j + k][i + h].rgbtBlue;

                    sumGreen += image[j + k][i + h].rgbtGreen;

                    sumRed += image[j + k][i + h].rgbtRed;

                    counter++;

                }

            }



            // averages the sum to make picture look blurrier

            temp[j][i].rgbtBlue = round(sumBlue / counter);

            temp[j][i].rgbtGreen = round(sumGreen / counter);

            temp[j][i].rgbtRed = round(sumRed / counter);

        }

    }



    //copies values from temporary table

    for (int i = 0; i < width; i++)

    {

        for (int j = 0; j < height; j++)

        {

            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;

            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;

            image[j][i].rgbtRed = temp[j][i].rgbtRed;

        }

    }

}
