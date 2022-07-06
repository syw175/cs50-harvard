#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++) 
    {
        for (int col = 0; col < width; col++) 
        {
            // Get a pointer to the current pixel and the calculate the required gray scale color
            RGBTRIPLE *currentColor = &image[row][col];
            BYTE grayScaleCol = round((currentColor->rgbtRed + currentColor->rgbtBlue
                                         + currentColor->rgbtGreen)/3.0);

            // Assign the gray scale color to the RGB values of the current pixel
            currentColor->rgbtRed = grayScaleCol;
            currentColor->rgbtBlue = grayScaleCol;
            currentColor->rgbtGreen = grayScaleCol;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0, n = width/2; col < n; col++)
        {
            // Swap current pixel with the next rightmost pixel
            RGBTRIPLE colorBuffer = image[row][col];
            image[row][col] = image[row][width-col-1];
            image[row][width-col-1] = colorBuffer;

            // Note: Pointers unnecessary here because C passes the address of the first value from image
            // RGBTRIPLE *currentColor = &image[row][col];
            // RGBTRIPLE *toBeReflected = &image[row][width-col-1];

            // RGBTRIPLE colorBuffer = image[row][col];
            // *currentColor = *toBeReflected;
            // *toBeReflected = colorBuffer;
        }
    }
    return;
}

// Blur image - TODO
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE adjPixels[6];
    int pixelCount = 0;

    for (int row = 0; row < height; row++) { 
        for (int col = 0; col < width; col++) { 

        }
    }


    return;
}

// Detect edges - TODO
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
