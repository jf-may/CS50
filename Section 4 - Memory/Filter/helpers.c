#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    const double one_third = 0.333333333333333333333333333333333333333333333333;
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int Gx_b, Gy_b, Gx_g, Gy_g, Gx_r, Gy_r;
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gx_b = Gy_b = Gx_g = Gy_g = Gx_r = Gy_r = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ind_i = i + di;
                    int ind_j = j + dj;

                    if (ind_i >= 0 && ind_i < height && ind_j >= 0 && ind_j < width)
                    {
                        Gx_b += image[ind_i][ind_j].rgbtBlue * Gx[di+1][dj+1];
                        Gy_b += image[ind_i][ind_j].rgbtBlue * Gy[di+1][dj+1];
                        Gx_g += image[ind_i][ind_j].rgbtGreen * Gx[di+1][dj+1];
                        Gy_g += image[ind_i][ind_j].rgbtGreen * Gy[di+1][dj+1];
                        Gx_r += image[ind_i][ind_j].rgbtRed * Gx[di+1][dj+1];
                        Gy_r += image[ind_i][ind_j].rgbtRed * Gx[di+1][dj+1];
                    }
                }
            }
            temp[i][j].rgbtBlue = (int) round(sqrt(Gx_b * Gx_b + Gy_b * Gy_b));
            temp[i][j].rgbtGreen = (int) round(sqrt(Gx_g * Gx_g + Gy_g * Gy_g));
            temp[i][j].rgbtRed = (int) round(sqrt(Gx_r * Gx_r + Gy_r * Gy_r));
            BYTE grayscale_pixel = (int) (temp[i][j].rgbtBlue
                + temp[i][j].rgbtRed + temp[i][j].rgbtGreen) * one_third;
            temp[i][j].rgbtBlue = grayscale_pixel;
            temp[i][j].rgbtGreen = grayscale_pixel;
            temp[i][j].rgbtRed = grayscale_pixel;
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
