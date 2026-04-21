#include "helpers.h"
#include "stdio.h"

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
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
