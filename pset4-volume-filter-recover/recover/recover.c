/*
 * Filename: recover.c
 *
 * Description: Recovers JPEGS from a forensic image
 *
 *
 * Author: Steven Wong
 * Date: July 10, 2022
 */




// The files you generate should each be named ###.jpg, where ### is a three-digit decimal number, 
// starting with 000 for the first image and counting up.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Images are blocks of 512 bytes
typedef uint8_t BYTE;

int main(int argc, char *argv[]) {

    // Validate that the user correctly provided the name of forensic image
    if (argc != 2) { 
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Name of a forensic image from which to recover JPEGS
    char *filename = argv[1];

    // Open the file for reading 
    FILE *recoveryFile = fopen(filename, "r");

    // Validate that file opening was successful and that the file is not NULL
    if (recoveryFile == NULL) { 
        return 1;
    }

    // Read blocks of 512 bytes until EOF is reached
    BYTE buffer[512];




    // Demo on ONE IMAGE FOR PROOF OF CONCEPT
    FILE *newfile = fopen("1.jpeg", "w");
    int test1 = 0;


    // CURRENTLY DEMOING ONE IMAGE - RESULT -> WORKING
    while (fread(buffer, sizeof(BYTE), 512, recoveryFile) == 512) { 

        // This should be working for detecting the start/end of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]>>4) == 0xe) { 
            // TEST
            test1++;
        }


        // TEST
        if (test1 == 1) { 
            fwrite(buffer, sizeof(BYTE), 512, newfile);
        }

        if (test1 == 2) { 
            break;
        }
        // TEST
        // blocksInCurrentImage++;
    }

    return 0;
}




