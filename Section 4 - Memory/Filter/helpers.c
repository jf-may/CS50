#include "helpers.h"
#include "stdio.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    const double one_third = 0.333333333333333333333333333333333333333333333333;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE grayscale_pixel = (int) (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) * one_third;
            image[i][j].rgbtBlue = grayscale_pixel;
            image[i][j].rgbtGreen = grayscale_pixel;
            image[i][j].rgbtRed = grayscale_pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    const int width_inv = width - 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width_inv - j];
            image[i][width_inv - j] = temp;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Checks image neighbors. Helper function for box blur

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int sum_b, sum_g, sum_r, count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sum_b = sum_g = sum_r = count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ind_i = i + di;
                    int ind_j = j + dj;

                    if (ind_i >= 0 && ind_i < height && ind_j >= 0 && ind_j < width)
                    {
                        sum_b += image[ind_i][ind_j].rgbtBlue;
                        sum_g += image[ind_i][ind_j].rgbtGreen;
                        sum_r += image[ind_i][ind_j].rgbtRed;
                        count++;
                    }
                }
            }
            temp[i][j].rgbtBlue = (int) sum_b / count;
            temp[i][j].rgbtGreen = (int) sum_g / count;
            temp[i][j].rgbtRed = (int) sum_r / count;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
