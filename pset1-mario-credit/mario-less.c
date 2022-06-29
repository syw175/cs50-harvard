/*
 * Filename: mario-less.c (Less Comfortable)
 *
 * Description: Recreate the pyramid of blocks in the beginning of World 1-1 from Super Mario Brothers
 * 
 * 
 * Author: Steven Wong
 * Date: June 28, 2022
 */


int main(void) {
	// Initialize initial value of height
    int height;

	// Get height from user within the range of [1-8] inclusive
    do {
    	height = get_int("Height: ");
    } 
	while (height < 1 || height > 8);  

    for (int row = 0; row < height; row++) {
        for (int space = height - row - 1; space > 0; space--) {
            printf(" ");
        }

        for (int hash = 0; hash < row + 1; hash++) {
            printf("#");
        }
        printf("\n");
    }

	return 0;
}



