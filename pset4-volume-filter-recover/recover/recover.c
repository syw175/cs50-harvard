/*
 * Filename: recover.c
 *
 * Description: Recovers JPEGS from a forensic image. Outputs files in ###.jpg where ###
 *              is a three-digit number, starting with 000 for the first image and counting up.
 *
 *
 * Author: Steven Wong
 * Date: July 10, 2022
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// Structure to represent blocks in FAT32 file system
typedef uint8_t BYTE;


int main(int argc, char *argv[]) {

    // Validate that the user correctly provided the name of forensic image
    if (argc != 2) {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the forensic image given in the command line from which to recover JPEGs
    char *filename = argv[1];
    FILE *recoveryFile = fopen(filename, "r");

    // Validate that file opening was successful and that the file is not NULL
    if (recoveryFile == NULL) {
        return 1;
    }

    // Initialize a buffer to store each 512-byte block of the file
    BYTE buffer[512];

    // Initialize a counter to keep track of the number of images recovered
    int fileCount = 0;
    int currentlyWriting = 0;
    FILE *output = NULL;
    char toSaveName[8];


    // Read the file in 512 byte chunks until end of file is reached
    while (fread(buffer, sizeof(BYTE), 512, recoveryFile) == 512) {

        // If the first four bytes are 0xff, 0xd8, 0xff, and 0xe[0-c], then it is a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]>>4) == 0xe) {

            // Create a string for the name of the file to be saved with the fileCount
            sprintf(toSaveName, "%.3i.jpg", fileCount);

            // Open the file for writing
            output = fopen(toSaveName, "w");

            // Set the flag to 1 to indicate that a new file is being written
            currentlyWriting = 1;

            // Increment the file count written so far
            fileCount++;
        }

        // If the current file is not NULL, write the buffer to the file
        if (currentlyWriting == 1) {
            fwrite(buffer, sizeof(BYTE), 512, output);
        }
    }

    // Close the file
    fclose(recoveryFile);
    fclose(output);
    return 0;
}




