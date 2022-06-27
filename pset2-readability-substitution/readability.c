/*
 * Filename: readability.c
 *
 * Description: Calculates the approximate grade level needed to comprehend some text
 *
 *
 * Author: Steven Wong
 * Date: June 27, 2022
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>


int count_sentences(char *text);
int count_letters(char *text);
int count_words(char *text);
int get_coleman_index(int letterCount, int wordCount, int sentenceCount);


int main(int argc, char *argv[]) {

    string string = get_string("Text: ");
    int letterCount = count_letters(string);
    int wordCount = count_words(string);
    int sentenceCount = count_sentences(string);
    int gradeIndex = get_coleman_index(letterCount, wordCount, sentenceCount);

    if (gradeIndex >= 16) {
        printf("Grade 16+\n");

    } else if (gradeIndex > 1) {
        printf("Grade %d\n", gradeIndex);

    } else {
        printf("Before Grade 1\n");
    }

    return 0;
}


int get_coleman_index(int letterCount, int wordCount, int sentenceCount) {
    // index = 0.0588 * L - 0.296 * S - 15.8
    // L = average number of letters per 100 words
    // S = average number of sentences per 100 words
    float L = 1.0 * letterCount / wordCount * 100;
    float S = 1.0 * sentenceCount / wordCount * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    return (int)round(index);
}


// Iterate through each chracter to count the words
int count_words(char *text) {
    int wordsCount = 0;

    for (int i = 0, n = strlen(text); i < n; i++) {
        // Check if the current character is a '-' and the previous character is a alphabetical
        // If true, word count is not increased
        if (text[i] == '-' && isalpha(text[i - 1])) {
            continue;
        }

        // Check if the current character is a '\'' and the previous character is a alphabetical
        // If true, word count is not increased
        else if (text[i] == 39 && isalpha(text[i - 1])) {
            continue;
        }

        // Check if the current caharacter is not alphabetical and if the previous character is alphabetical
        // If true, then it must be the start of a new word
        else if (!isalpha(text[i]) && isalpha(text[i - 1])) {
            wordsCount++;
        }
    }
    return wordsCount;
}


// Iterate through each character, if the character is a [".", ",", "!"], then it must be a new sentence
int count_sentences(char *text) {
    int sentencesCount = 0;

    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
            sentencesCount++;
        }
    }
    return sentencesCount;
}


// Iterate through each chracter, if the character is alphabetical, then it must be a new letter
int count_letters(char *text) {
    int lettersCount = 0;

    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            lettersCount++;
        }
    }
    return lettersCount;
}