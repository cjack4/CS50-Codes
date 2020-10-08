// The partner file for "filters," this I wrote this file to tell filters.c HOW to apply a given filter to a bitmap image. 

#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row
    for (int h = 0; h < height; h++)
    {
        // for each pixel
        for (int w = 0; w < width; w++)
        {
            int gray = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / (float)3);
            image[h][w].rgbtBlue = (gray);
            image[h][w].rgbtGreen = (gray);
            image[h][w].rgbtRed = (gray);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row
    for (int h = 0; h < height; h++)
    {
        // for each pixel
        for (int w = 0; w < width; w++)
        {
            int sepiaRed = round((0.393 * image[h][w].rgbtRed) + (0.769 * image[h][w].rgbtGreen) + (0.189 * image[h][w].rgbtBlue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            int sepiaGreen = round((0.349 * image[h][w].rgbtRed) + (0.686 * image[h][w].rgbtGreen) + (0.168 * image[h][w].rgbtBlue));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            int sepiaBlue = round((0.272 * image[h][w].rgbtRed) + (0.534 * image[h][w].rgbtGreen) + (0.131 * image[h][w].rgbtBlue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row
    for (int h = 0; h < height; h++)
    {
        int last = width - 1;

        // for each pixel up to halfway through the row
        for (int w = 0; w < round(width / 2); w++)
        {
            // create a temp
            RGBTRIPLE temp1;

            // temp gets current pixel
            temp1 = image[h][w];

            // current pixel gets last pixel's values
            image[h][w] = image[h][last];

            // last pixel gets current pixel's values
            image[h][last] = temp1;

            // move to next-to-last
            last -= 1;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // declare function
    RGBTRIPLE compute(int a, int b, RGBTRIPLE image[a][b], int c, int d);

    // create a temp
    RGBTRIPLE blurred[height][width];

    // for each row
    for (int h = 0; h < height; h++)
    {
        // for each pixel
        for (int w = 0; w < width; w++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            float count = 0.00;

            // If on the Left edge
            if (w == 0)
            {
                // top left corner
                if (h == 0)
                {
                    for (int i = 0; i <= 1; i++)
                    {
                        for (int j = 0; j <= 1; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }

                // bottom left corner
                else if (h == height - 1)
                {
                    for (int i = height - 2; i < height; i++)
                    {
                        for (int j = 0; j <= 1; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }

                // left edge middle of rows
                else
                {
                    for (int i = h - 1; i <= h + 1; i++)
                    {
                        for (int j = w; j <= w + 1; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }
            }

            // If on the Right edge
            else if (w == width - 1)
            {
                // top right corner
                if (h == 0)
                {
                    for (int i = 0; i <= 1; i++)
                    {
                        for (int j = w - 1; j <= w; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }

                // bottom right corner
                else if (h == height - 1)
                {
                    for (int i = h - 1; i <= h; i++)
                    {
                        for (int j = w - 1; j <= w; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }

                else // right edge middle rows
                {
                    for (int i = h - 1; i <= h + 1; i++)
                    {
                        for (int j = w - 1; j <= w; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }
            }

            else
            {
                // if on top row
                if (h == 0)
                {
                    for (int i = 0; i <= 1; i++)
                    {
                        for (int j = w - 1; j <= w + 1; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }

                // bottom row
                else if (h == height - 1)
                {
                    for (int i = h - 1; i <= h; i++)
                    {
                        for (int j = w - 1; j <= w + 1; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }

                else
                {
                    for (int i = h - 1; i <= h + 1; i++)
                    {
                        for (int j = w - 1; j <= w + 1; j++)
                        {
                            blue += image[i][j].rgbtBlue;
                            green += image[i][j].rgbtGreen;
                            red += image[i][j].rgbtRed;
                            count++;
                        }
                    }
                }
            }

            blurred[h][w].rgbtBlue = round(blue / count);
            blurred[h][w].rgbtGreen = round(green / count);
            blurred[h][w].rgbtRed = round(red / count);
        }
    }

    // Copy into image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = blurred[h][w];
        }
    }
    return;
}
