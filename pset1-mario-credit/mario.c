/*
 * Filename: mario.c (More Comfortable)
 *
 * Description: Recreate the pyramid of blocks in the beginning of World 1-1 from Super Mario Brothers
 * 
 * 
 * Author: Steven Wong
 * Date: June 26, 2022
 */


#include<stdio.h>

int main (int argc, char **argv) { 
    // Initialize initial value of height that is invalid 
    int height = -1; 

    // Get height from user within the range of [1-8] inclusive
    while (height <= 0 || height > 8) { 
        printf("Height: "); 
        scanf("%d", &height);
    }

    // Print lines 
    for (int row = height; row > 0; row--) { 
        
        // Print LHS mario spaces
        for (int k = 0; k < row-1; k++) { 
            printf(" ");
        }

        // Print LHS mario hashes 
        for (int k = 0; k < height - row + 1; k++) { 
            printf("#");
        }

        // Print 2 width space between pyramids
        printf("  "); 

        // Print RHS mario hashes
        for (int k = 0; k < height - row + 1; k++) { 
            printf("#");
        }

        // Print newline for each new line
        printf("\n");
    }

    return 0;
}
