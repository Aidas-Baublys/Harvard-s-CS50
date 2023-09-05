#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00;
            int rounded = round(avg);
            image[i][j].rgbtBlue = rounded;
            image[i][j].rgbtGreen = rounded;
            image[i][j].rgbtRed = rounded;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tempPixel = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tempPixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg_count = 0, red_sum = 0, blue_sum = 0, green_sum = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x < 0 || x >= height || y < 0 || y >= width)
                    {
                        continue;
                    }
                    red_sum += image[x][y].rgbtRed;
                    blue_sum += image[x][y].rgbtBlue;
                    green_sum += image[x][y].rgbtGreen;
                    avg_count++;
                }
            }
            temp_image[i][j].rgbtRed = round(red_sum / avg_count);
            temp_image[i][j].rgbtBlue = round(blue_sum / avg_count);
            temp_image[i][j].rgbtGreen = round(green_sum / avg_count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0, gx_green = 0, gx_blue = 0, gy_red = 0, gy_green = 0, gy_blue = 0;
            int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    if (i - 1 + x < 0 || i - 1 + x >= height || j - 1 + y < 0 || j - 1 + y >= width)
                    {
                        continue;
                    }
                    gx_red += image[i - 1 + x][j - 1 + y].rgbtRed * gx[x][y];
                    gx_green += image[i - 1 + x][j - 1 + y].rgbtGreen * gx[x][y];
                    gx_blue += image[i - 1 + x][j - 1 + y].rgbtBlue * gx[x][y];
                    gy_red += image[i - 1 + x][j - 1 + y].rgbtRed * gy[x][y];
                    gy_green += image[i - 1 + x][j - 1 + y].rgbtGreen * gy[x][y];
                    gy_blue += image[i - 1 + x][j - 1 + y].rgbtBlue * gy[x][y];
                }
            }
            int red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));
            int green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            temp[i][j].rgbtBlue = blue > 255 ? 255 : blue;
            temp[i][j].rgbtGreen = green > 255 ? 255 : green;
            temp[i][j].rgbtRed = red > 255 ? 255 : red;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
