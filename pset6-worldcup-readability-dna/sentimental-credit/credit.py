# Get credit number from the user in string form
number = input("Number: ")
# Initialize credit number sum to 0
sumCardDigits = 0
# Valid starting digits for AMEX and MASTERCARD
AMEX = [34, 37]
MASTERCARD = [51, 52, 53, 54, 55]

# Multiply every other digit in the number and sum their digits
for digit in number[-2::-2]:
    # Convert digit to int and multiply by 2
    currentNumber = int(digit)*2
    # If the number is greater than 9, add the second digit to the sum and divide by 10
    if currentNumber >= 10:
        sumCardDigits += currentNumber % 10
        currentNumber //= 10

    # Add the first digit to the sum
    sumCardDigits += currentNumber

# Sum previous number with the sum of digits that weren't multiplied by 2
for digit in number[-1::-2]:
    sumCardDigits += int(digit)

# Check if the last digit is 0, if not, card is invaid
if sumCardDigits % 10 != 0:
    print("INVALID")

# Get the starting 2 digits
startingDigits = int(number[0] + number[1])

# If the starting digits is 34 or 37, then the card is AMEX
if startingDigits in AMEX:
    print("AMEX")

# If the starting digits is 51, 52, 53, 54, or 55.. then the card is MASTERCARD
if startingDigits in MASTERCARD:
    print("MASTERCARD")

# If the starting digit is 0, then the card is VISA
if number[0] == '4':
    print("VISA")