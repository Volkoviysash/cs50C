#include "helpers.h"
#include <math.h>

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            average = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    const int MAXVALUE = 255;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int ForRed = round(0.393*image[h][w].rgbtRed + 0.769*image[h][w].rgbtGreen + 0.189*image[h][w].rgbtBlue);
            int ForGreen = round(0.349*image[h][w].rgbtRed + 0.686*image[h][w].rgbtGreen + 0.168*image[h][w].rgbtBlue);
            int ForBlue = round(0.272*image[h][w].rgbtRed + 0.534*image[h][w].rgbtGreen + 0.131*image[h][w].rgbtBlue);


            image[h][w].rgbtRed = LesserOfTwo (ForRed, MAXVALUE);
            image[h][w].rgbtGreen = LesserOfTwo (ForGreen, MAXVALUE);
            image[h][w].rgbtBlue = LesserOfTwo (ForBlue, MAXVALUE);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width/2; w++)
        {
            temp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = temp;
        }
    }
    return;
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float count = 0;
    int sum = 0;
    for (int h = i - 1; h <= (i+1); h++)
    {
        for (int w = j - 1; w <= (j+1); w++)
        {
            if(h < 0 || h >= height || w < 0 || w >= width)
            {
                continue;
            }
            if(color_position == RED_COLOR)
            {
                sum += image[h][w].rgbtRed;
            }
            else if(color_position == GREEN_COLOR)
            {
                sum += image[h][w].rgbtGreen;
            }
            else if(color_position == BLUE_COLOR)
            {
                sum += image[h][w].rgbtBlue;
            }
            count++;
        }
    }
    return round(sum/count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height-3; h++)
    {
        for (int w = 0; w < width-3; w++)
        {
            copy[h][w] = image[h][w];
        }
    }

    RGBTRIPLE blurbufer[height][width];
    //Each pixel
    for (int h = 0; h < height-3; h++)
    {
        for (int w = 0; w < width-3; w++)
        {
            image[h][w].rgbtRed = getBlur(h, w, height, width, copy, RED_COLOR);
            image[h][w].rgbtGreen = getBlur(h, w, height, width, copy, GREEN_COLOR);
            image[h][w].rgbtBlue = getBlur(h, w, height, width, copy, BLUE_COLOR);
        }
    }
    return;
}

int LesserOfTwo (int a, int b)
{
    if (a < b)
    return a;
    else
    return b;
}