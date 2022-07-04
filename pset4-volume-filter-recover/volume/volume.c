/*
 * Filename: volume.c
 *
 * Description: Modifies the volume of an audio file. Takes 3 CLI arguments:
 *              1. 'Inputfile.WAV'
 *              2. 'Outputfile.WAV'
 *              3. Floating point scale factor to modify volume by
 *
 *
 * Author: Steven Wong
 * Date: July 4, 2022
 */


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t HEADER_BYTE;
typedef int16_t AUDIO_BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    HEADER_BYTE headerBuffer[HEADER_SIZE];
    fread(headerBuffer, sizeof(HEADER_BYTE), HEADER_SIZE, input);
    fwrite(headerBuffer, sizeof(HEADER_BYTE), HEADER_SIZE, output);


    // Read samples from input file and write updated data to output file
    AUDIO_BYTE audioBuffer;
    while (fread(&audioBuffer, sizeof(AUDIO_BYTE), 1, input) == 1)
    {
        audioBuffer *= factor;
        fwrite(&audioBuffer, sizeof(AUDIO_BYTE), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);


    return 0;
}
