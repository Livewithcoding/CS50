#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float media_cores;

    // Cycle through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Substitutes for the average of colors
            media_cores = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);

            image[i][j].rgbtBlue = media_cores;
            image[i][j].rgbtGreen = media_cores;
            image[i][j].rgbtRed = media_cores;
        }
    }

    return;
}


int limit(int color)
{
    if (color > 255)
    {
        color = 255;
    }

    return color;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;

    // Cycle through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Substitutes for the formula value
            sepiaRed = limit(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            sepiaGreen = limit(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            sepiaBlue = limit(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Width to be switched
    int tmp_width = width - 1;

    // Exchange the pixel from the beginning to the end
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][tmp_width - j]);
        }
    }

    return;
}

// Function to exchange values
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

int lineStart, lineEnd, columnStart, columnEnd;

void blurMatrix(int i, int j, int height, int width);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            double count = 0.0;

            blurMatrix(i, j, height, width);

            for (int h = lineStart; h <= lineEnd; h++)
            {
                for (int w = columnStart; w <= columnEnd; w++)
                {
                    sumRed += tmp_image[h][w].rgbtRed;
                    sumGreen += tmp_image[h][w].rgbtGreen;
                    sumBlue += tmp_image[h][w].rgbtBlue;

                    count++;
                }
            }
            image[i][j].rgbtRed = limit(round(sumRed / count));
            image[i][j].rgbtGreen = limit(round(sumGreen / count));
            image[i][j].rgbtBlue = limit(round(sumBlue / count));
        }
    }

    return;
}

void blurMatrix(int i, int j, int height, int width)
{
    if (i - 1 < 0)
    {
        lineStart = i;
    }
    else
    {
        lineStart = i - 1;
    }

    if (i + 1 >= height)
    {
        lineEnd = i;
    }
    else
    {
        lineEnd = i + 1;
    }

    if (j - 1 < 0)
    {
        columnStart = j;
    }
    else
    {
        columnStart = j - 1;
    }

    if (j + 1 >= width)
    {
        columnEnd = j;
    }
    else
    {
        columnEnd = j + 1;
    }
}