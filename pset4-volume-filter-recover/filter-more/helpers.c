#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Function prototypes
RGBTRIPLE getAverageNeighborColors (int height, int width, RGBTRIPLE image[height][width], int row, int col);


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


// Blur image using average of neighoring pixels
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a deep copy of image for manipulation
    RGBTRIPLE imageCopy[height][width];

    // Copy image to imageCopy
    for (int i = 0; i < height; i++) {
        for (int y = 0; y < width; y++) {
            imageCopy[i][y] = image[i][y];
        }
    }

    // Iterate over image and blur each pixel
    for (int row = 0; row < height; row++) { 
        for (int col = 0; col < width; col++) { 
            RGBTRIPLE currentColor = imageCopy[row][col];
            image[row][col] = getAverageNeighborColors(height, width, imageCopy, row, col);
        }
    }
    return;
}

// Detect edges - TODO
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}


// Get average color value of surrounding pixels given an image and a pixel location
RGBTRIPLE getAverageNeighborColors (int height, int width, RGBTRIPLE image[height][width], int row, int col) {
    
    // Initialize counter variables 
    int sumRed = 0;
    int sumBlue = 0;
    int sumGreen = 0;
    int pixelsCounted = 0;

    // Iterate through surrounding pixels and add their RGB values to the sum
    for (int i = -1; i <= 1; i++) {
        // If current row is out of bounds, move to the next row
        if (row + i < 0 || row + i >= height) { 
            continue;
        }

        // If valid row... check adjacent pixels 
        for (int j = -1; j <= 1; j++) {
            // If current column is out of bounds, move to the next column
            if (col + j < 0 || col + j >= width) { 
                continue;
            }

            // If valid column... add pixel value to sum
            sumRed += image[row + i][col + j].rgbtRed;
            sumBlue += image[row + i][col + j].rgbtBlue;
            sumGreen += image[row + i][col + j].rgbtGreen;
            pixelsCounted++;
        }
    }

    // Calculate average color value for surrounding pixels
    RGBTRIPLE averageColor;
    averageColor.rgbtRed = round((float)sumRed / pixelsCounted);
    averageColor.rgbtBlue = round((float)sumBlue / pixelsCounted);
    averageColor.rgbtGreen = round((float)sumGreen / pixelsCounted);

    // Return average color value
    return averageColor;
}