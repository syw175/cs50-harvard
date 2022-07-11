/*
 * Filename: helpers.c
 *
 * Description: Applies filters to bitmap images (BMP) such as conversion to grayscale,
 *              blurring, reflecting, and detection of edges.
 *
 *
 * Author: Steven Wong
 * Date: July 10, 2022
 */


#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


// Struct for sobel filter output
typedef struct {
    int weightedRedVal;
    int weightedBlueVal;
    int weightedGreenVal;
} sobelResult;


// Function prototypes
RGBTRIPLE getAverageNeighborColors (int height, int width, RGBTRIPLE image[height][width], int row, int col);
sobelResult computeGyKernal (int height, int width, RGBTRIPLE image[height][width], int row, int col);
sobelResult computeGxKernal (int height, int width, RGBTRIPLE image[height][width], int row, int col);
RGBTRIPLE combineSobelValues(sobelResult gxValue, sobelResult gyValue);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {

    // Loop through each row
    for (int row = 0; row < height; row++) {
        // Loop through each column
        for (int col = 0; col < width; col++) {

            // Get a pointer to the current pixel and the calculate the required gray scale color
            RGBTRIPLE *currentColor = &image[row][col];

            // Calculate the gray scale color by averaging the red, green, and blue values
            BYTE grayScaleCol = round((currentColor->rgbtRed + currentColor->rgbtBlue
                                         + currentColor->rgbtGreen)/3.0);

            // Set the red, green, and blue values to the gray scale color
            currentColor->rgbtRed = grayScaleCol;
            currentColor->rgbtBlue = grayScaleCol;
            currentColor->rgbtGreen = grayScaleCol;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {

    // Loop through each row
    for (int row = 0; row < height; row++) {
        // Loop through each column
        for (int col = 0, n = width/2; col < n; col++) {

            // Temporary variable to store the current pixel
            RGBTRIPLE colorBuffer = image[row][col];

            // Set the current pixel to the pixel at the end of the row
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
void blur(int height, int width, RGBTRIPLE image[height][width]) {

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

            // Get the average color of the neighboring pixels
            RGBTRIPLE currentColor = imageCopy[row][col];
            image[row][col] = getAverageNeighborColors(height, width, imageCopy, row, col);
        }
    }
    return;
}


// Detect edges using sobel filter
void edges (int height, int width, RGBTRIPLE image[height][width]) {

    // Create a deep copy of the original image
    RGBTRIPLE imageCopy[height][width];
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            imageCopy[row][col] = image[row][col];
        }
    }

    // Iterate over image and apply sobel filter to each pixel
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            // Get the sobel values for the current pixel
            sobelResult gxVal, gyVal;
            // Compute the x direction sobel value
            gxVal = computeGxKernal(height, width, imageCopy, row, col);
            // Compute the y direction sobel value
            gyVal = computeGyKernal(height, width, imageCopy, row, col);
            // Combine the sobel values to get the final sobel value
            image[row][col] = combineSobelValues(gxVal, gyVal);
        }
    }

    return;
}

// Helper function to calculate final sobel value
RGBTRIPLE combineSobelValues(sobelResult gxValue, sobelResult gyValue) {

    // Initialize color struct to store the final sobel value
    RGBTRIPLE result;

    // If the red sobel value is greater than 255, set it to 255
    if (sqrt(pow(gxValue.weightedRedVal, 2) + pow(gyValue.weightedRedVal, 2)) > 255) {
        result.rgbtRed = 255;
    } else {
        result.rgbtRed = round(sqrt((pow(gxValue.weightedRedVal, 2) + pow(gyValue.weightedRedVal, 2))));
    }

    // If the green sobel value is greater than 255, set it to 255
    if (sqrt(pow(gxValue.weightedGreenVal, 2) + pow(gyValue.weightedGreenVal, 2)) > 255) {
        result.rgbtGreen = 255;
    } else {
        result.rgbtGreen = round(sqrt((pow(gxValue.weightedGreenVal, 2) + pow(gyValue.weightedGreenVal, 2))));
    }

    // If the blue sobel value is greater than 255, set it to 255
    if (sqrt(pow(gxValue.weightedBlueVal, 2) + pow(gyValue.weightedBlueVal, 2)) > 255) {
        result.rgbtBlue = 255;
    } else {
        result.rgbtBlue = round(sqrt((pow(gxValue.weightedBlueVal, 2) + pow(gyValue.weightedBlueVal, 2))));
    }

    // Return the final sobel value
    return result;
}


// Detect edges in the y direction by computing the gY kernal
sobelResult computeGyKernal (int height, int width, RGBTRIPLE image[height][width], int row, int col) {

    // Initialize "kernals" to detect edges in the Y direction
    int gyKernal[3][3]= {{-1, -2, -1},
                         {0, 0, 0},
                         {1, 2, 1}};

    // Initalize counter variables
    int weightedSumRed = 0;
    int weightedSumBlue = 0;
    int weightedSumGreen = 0;

    // Iterate through surrounding pixels and add their weighted RGB values to sum
    for (int i = -1; i <= 1; i++) {
        // If current row is out of bounds, skip it and move to the next row
        if (row + i < 0 || row + i >= height) {
            continue;
        }
        // If valid row... check adjacent pixels
        for (int j = -1; j <= 1; j++) {
            // If current column is out of bounds, skip it and move to the next pixel
            if (col + j < 0 || col + j >= width) {
                continue;
            }

            // Do calculation and add to the weightSums
            int currentKernalHeight = i + 1;
            int currentKernalWidth = j + 1;

            // Add weighted RGB values to sums
            weightedSumRed += gyKernal[currentKernalHeight][currentKernalWidth] * image[row + i][col + j].rgbtRed;
            weightedSumBlue += gyKernal[currentKernalHeight][currentKernalWidth] * image[row + i][col + j].rgbtBlue;
            weightedSumGreen += gyKernal[currentKernalHeight][currentKernalWidth] * image[row + i][col + j].rgbtGreen;
        }
    }
    // Calculate resulting color value for surrounding pixels
    sobelResult sobelValY;
    sobelValY.weightedRedVal = weightedSumRed;
    sobelValY.weightedGreenVal = weightedSumGreen;
    sobelValY.weightedBlueVal = weightedSumBlue;

    // Return the y direction sobel value
    return sobelValY;
}


// Detect edges in the x direction by computing the gX kernal
sobelResult computeGxKernal (int height, int width, RGBTRIPLE image[height][width], int row, int col) {

    // Initialize "kernals" to detect edges in the X direction
    int gxKernal[3][3] = {{-1, 0, 1},
                          {-2, 0, 2},
                          {-1, 0, 1}};

    // Initalize counter variables
    int weightedSumRed = 0;
    int weightedSumBlue = 0;
    int weightedSumGreen = 0;

    // Iterate through surrounding pixels and add their weighted RGB values to sum
    for (int i = -1; i <= 1; i++) {
        // If current row is out of bounds, skip it and move to the next row
        if (row + i < 0 || row + i >= height) {
            continue;
        }
        // If valid row... check adjacent pixels
        for (int j = -1; j <= 1; j++) {
            // If current column is out of bounds, skip it and move to the next pixel
            if (col + j < 0 || col + j >= width) {
                continue;
            }

            // Do calculation and add to the weightSums
            int currentKernalHeight = i + 1;
            int currentKernalWidth = j + 1;

            // Add weighted RGB values to sums
            weightedSumRed += gxKernal[currentKernalHeight][currentKernalWidth] * image[row + i][col + j].rgbtRed;
            weightedSumBlue += gxKernal[currentKernalHeight][currentKernalWidth] * image[row + i][col + j].rgbtBlue;
            weightedSumGreen += gxKernal[currentKernalHeight][currentKernalWidth] * image[row + i][col + j].rgbtGreen;
        }
    }

    // Calculate resulting color value for surrounding pixels
    sobelResult sobelValX;
    sobelValX.weightedRedVal = weightedSumRed;
    sobelValX.weightedGreenVal = weightedSumGreen;
    sobelValX.weightedBlueVal = weightedSumBlue;

    // Return the x direction sobel value
    return sobelValX;
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