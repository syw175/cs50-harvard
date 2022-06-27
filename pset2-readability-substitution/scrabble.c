/*
 * Filename: scrabble.c
 *
 * Description: A short game of scrabble recreated in C
 * 
 * 
 * Author: Steven Wong
 * Date: June 27, 2022
 */

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the words entered by both players
    printf("Player 1: %s\nPlayer2: %s\n", word1, word2);

    // Print the winner
    if(score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score2 > score1) {
        printf("Player 2 wins!\n");
    } else { 
        printf("It's a tie!\n");
    }

    return 0;
}

int compute_score(string word) {
    // Compute and return score for string
    int score = 0;


    for (int i = 0; i < strlen(word); i++) { 
        // Check if the current char is an alphabetical character
        if (!isalpha(word[i])) { 
            continue; 
        }

        // Current current char to uppercase and substract 65 to match the POINTS index values
        char currentChar = toupper(word[i]);
        score += POINTS[(int)(currentChar - 'A')];
    }
    return score;
}
