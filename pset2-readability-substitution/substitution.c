/*
 * Filename: readability.c
 *
 * Description: implements a substitution cipher, per the below test cases.
 * 
 * 
 * Sample Test Case:
 * $ ./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ
 * plaintext:  HELLO
 * ciphertext: VKXXN
 * 
 * 
 * Author: Steven Wong
 * Date: June 27, 2022
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>


const char* decryptMessage(char message[], char cipher[]);


int main(int argc, char** argv) {
    // If no arguments are given, remind the user about the proper usage of substitution.c
    if (argc != 2) { 
        printf("Usage: ./substitution key\n");
        return 2;
    }

    // If the cipher key is not given in the correct format, remind the user of the cipher format.
    if (strlen(argv[1]) != 26) { 
        printf("Key must contain 26 characters\n");
        return 1;
    }


    string message = get_string("Please enter your plain text: ");
    printf("The decrypted message of %s is %s\n", message, decryptMessage(message, argv[1]));

    return 0;
}


const char* decryptMessage(char message[], char cipher[]) {
    // Initialize a new array on the heap based on the size of the string
    char* decryptedMessage = malloc(strlen(message) * sizeof(char));

    // Decipher each char in the given message with the cipher key
    for (int i = 0; i < strlen(message); i++) { 
        
        // Check is the character is an alphabetical char
        if (!isalpha(message[i])) {
            decryptedMessage[i] = message[i];
            continue; 
        }

        // Decipher lower case characters with the cipher key
        if (islower(message[i])) {
            char newChar = cipher[message[i] - 'a'];
            decryptedMessage[i] = tolower(newChar);
        }

        // Decipher upper case characers with the cipher key 
        if (isupper(message[i])) { 
            char newChar = cipher[message[i] - 'A']; 
            decryptedMessage[i] = toupper(newChar);
        }
    }
    return decryptedMessage;
}
