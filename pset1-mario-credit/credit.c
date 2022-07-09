/*
 * Filename: credit.c
 *
 * Description: Determine whether a number is a valid credit card. If so, prints out what type of credit card it is.
 *
 *
 * Author: Steven Wong
 * Date: June 26, 2022
 */


#include<stdio.h>
#include<cs50.h>


// Get the number of digits in a number
int getNumLength (long num) {

    // Initialize the number of digits
    int count = 0;

    // Loop through the number
    while (num > 0) {

        // Divide the number by 10
        num /= 10;
        count++;
    }

    // Return the number of times the number was divided by 10 to get the number of digits
    return count;
}


// Check if a long number is divisible by 10
int isDivisibleBy10 (long num) {
    return num % 10 == 0;
}


// Get Starting Digits (2)
long getStartingDigits(long num) {

    // Divide by 10 until the number has only two digits
    while (num >= 100) {
        num /= 10;
    }

    // Return the starting digits of the original number
    return num;
}


int main (int argc, char **argv) {
    // Initialize variables
    long ccNum;
    int sumOddDigits = 0;
    int sumEvenDigits = 0;

    // Ask the user for a credit card number until a valid number is given
    do {
        ccNum = get_long("Number: ");
    } while(ccNum <= 0);

    // Get the starting digits of the credit card number
    long startingDigits = getStartingDigits(ccNum);
    // Get the number of digits in the credit card number
    int numLength = getNumLength(ccNum);


    // Check if the credit is of a valid length, if they are not, print an error message
    if (numLength != 13 && numLength != 15 && numLength!= 16) {
        printf("INVALID\n");
        return 0;
    }

    // Determine if the credit card number is valid
    do {
        
    // Remove right most digit and add to sumEvenDigits
    sumEvenDigits += ccNum % 10;
    ccNum /= 10;

    // Remove next digit and multiply it by 2 before adding to sumOddDigits
    long mod2 = (ccNum % 10) * 2;
    long digit1 = mod2 % 10;
    long digit2 = mod2 / 10;

    // Split two digit numbers into 2 before adding to sumOddDigits
    sumOddDigits += digit1 + digit2;
    ccNum /= 10;
    } while (ccNum > 0);

    // If the result of Luhn's Algorithm is not divisble by 10, it is not a valid credit card #
    if (!isDivisibleBy10(sumEvenDigits+sumOddDigits)) {
        printf("INVALID\n");
        return 0;
    }

    // Determine which type of credit card it is based on the starting digits
    if (startingDigits == 34 || startingDigits == 37) {
        printf("AMEX\n");

    } else if (startingDigits >= 51 && startingDigits <= 55) {
        printf("MASTERCARD\n");

    } else if (startingDigits/10 == 4) {
        printf("VISA\n");

    } else {
        printf("INVALID\n");
    }
    return 0;
}