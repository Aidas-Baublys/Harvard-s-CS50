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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;
            float red = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float green = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float blue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            image[i][j].rgbtRed = red >= 255 ? 255 : round(red);
            image[i][j].rgbtGreen = green >= 255 ? 255 : round(green);
            image[i][j].rgbtBlue = blue >= 255 ? 255 : round(blue);
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
