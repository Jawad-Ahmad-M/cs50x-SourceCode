#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE originalRed = image[i][j].rgbtRed;     // It gives original red colour
            BYTE originalBlue = image[i][j].rgbtBlue;   // It gives original blue color
            BYTE originalGreen = image[i][j].rgbtGreen; // It gives original green color

            if (originalRed == originalBlue && originalBlue == originalGreen)
            {
                continue;
            }
            BYTE resultByte = round((originalRed + originalBlue + originalGreen) /
                                    3.0); // Takes average of All colours

            // Sets all colors to average value, so it becomes grey with proper brightness.
            image[i][j].rgbtBlue = resultByte;
            image[i][j].rgbtRed = resultByte;
            image[i][j].rgbtGreen = resultByte;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE max = 255;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE originalRed = image[i][j].rgbtRed;     // It gives original red colour
            BYTE originalGreen = image[i][j].rgbtGreen; // It gives original green color
            BYTE originalBlue = image[i][j].rgbtBlue;   // It gives original blue color

            // Convert all colours to their sepia colours ratios.
            int Red = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int Green = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int Blue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // Sets the sepia colours into range.
            BYTE sepiaRed = (Red > 255) ? max : (BYTE) Red;
            BYTE sepiaBlue = (Blue > 255) ? max : (BYTE) Blue;
            BYTE sepiaGreen = (Green > 255) ? max : (BYTE) Green;

            // Sets all colors to average value, so it becomes grey with proper brightness.
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *a = &image[i][j];
            RGBTRIPLE *b = &image[i][width - j - 1];

            // Swapping of pixels
            RGBTRIPLE temp = *a;
            *a = *b;
            *b = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width]; // Initialzed a copy of real image
    BYTE max = 255;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 1;

            BYTE originalRed = image[i][j].rgbtRed;     // It gives original red colour
            BYTE originalGreen = image[i][j].rgbtGreen; // It gives original green color
            BYTE originalBlue = image[i][j].rgbtBlue;   // It gives original blue color

            int sumRed = (int) originalRed;
            int sumGreen = (int) originalGreen;
            int sumBlue = (int) originalBlue;

            // All Pixels Around the selected One

            if ((j + 1) < width) // Right pixel
            {
                sumRed += image[i][j + 1].rgbtRed;
                sumGreen += image[i][j + 1].rgbtGreen;
                sumBlue += image[i][j + 1].rgbtBlue;
                count++;
            }
            if ((j - 1) >= 0) // Left pixel
            {
                sumRed += image[i][j - 1].rgbtRed;
                sumGreen += image[i][j - 1].rgbtGreen;
                sumBlue += image[i][j - 1].rgbtBlue;
                count++;
            }
            if ((i - 1) >= 0) // Upper pixel
            {
                sumRed += image[i - 1][j].rgbtRed;
                sumGreen += image[i - 1][j].rgbtGreen;
                sumBlue += image[i - 1][j].rgbtBlue;
                count++;
            }
            if ((i + 1) < height) // Lower pixel
            {
                sumRed += image[i + 1][j].rgbtRed;
                sumGreen += image[i + 1][j].rgbtGreen;
                sumBlue += image[i + 1][j].rgbtBlue;
                count++;
            }
            if ((i - 1) >= 0 && (j + 1) < width) // Upper Right pixel
            {
                sumRed += image[i - 1][j + 1].rgbtRed;
                sumGreen += image[i - 1][j + 1].rgbtGreen;
                sumBlue += image[i - 1][j + 1].rgbtBlue;
                count++;
            }
            if ((i - 1) >= 0 && (j - 1) >= 0) // Upper Left pixel
            {
                sumRed += image[i - 1][j - 1].rgbtRed;
                sumGreen += image[i - 1][j - 1].rgbtGreen;
                sumBlue += image[i - 1][j - 1].rgbtBlue;
                count++;
            }
            if ((i + 1) < height && (j + 1) < width) // Lower Right pixel
            {
                sumRed += image[i + 1][j + 1].rgbtRed;
                sumGreen += image[i + 1][j + 1].rgbtGreen;
                sumBlue += image[i + 1][j + 1].rgbtBlue;
                count++;
            }
            if ((i + 1) < height && (j - 1) >= 0) // Lower Left pixel
            {
                sumRed += image[i + 1][j - 1].rgbtRed;
                sumGreen += image[i + 1][j - 1].rgbtGreen;
                sumBlue += image[i + 1][j - 1].rgbtBlue;
                count++;
            }

            int blurRed = round(sumRed / (float) count);
            int blurGreen = round(sumGreen / (float) count);
            int blurBlue = round(sumBlue / (float) count);

            blurRed = (blurRed > 255) ? max : (BYTE) blurRed;
            blurGreen = (blurGreen > 255) ? max : (BYTE) blurGreen;
            blurBlue = (blurBlue > 255) ? max : (BYTE) blurBlue;

            image2[i][j].rgbtRed = (BYTE) blurRed;     // Assings red color to copy of real image
            image2[i][j].rgbtGreen = (BYTE) blurGreen; // Assings green color to copy of real image
            image2[i][j].rgbtBlue = (BYTE) blurBlue;   // Assings blue color to copy of real image
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image2[i][j]; // Re-Asigns the copied colors to real image
        }
    }

    return;
}
