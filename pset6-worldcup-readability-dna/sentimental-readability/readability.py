from operator import le
import re  # For regex statements


def main():
    # Get text to be analyzed from the user
    text = input("Text: ")

    # Use regular expressions to get the letter, word, and number count
    letterCount = len(re.findall("[a-zA-z]", text))
    wordCount = len(text.split());
    sentenceCount = len(re.findall("[?.!]", text))

    # Calculate the grade index using the Coleman-Liau algorithmn
    gradeIndex = getColemanIndex(letterCount, wordCount, sentenceCount)

    # If grade index is greater than or equal to 16, print Grade 16+
    if (gradeIndex >= 16):
        print("Grade 16+");

    # If the grade is greater than or equal to 1, print the grade 
    elif (gradeIndex > 1):
        print(f"Grade {gradeIndex}")

    # Otherwise, print before grade 1
    else:
        print("Before Grade 1")


# Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8
def getColemanIndex(letterCount, wordCount, sentenceCount):
    # Compute average number of letters per 100 words
    L = letterCount / wordCount * 100

    # Compute average number of sentences per 100 words
    S = sentenceCount / wordCount * 100

    # Return index rounded to the nearest integer
    return round(0.0588 * L - 0.296 * S - 15.8)


# Start main function
if __name__ == "__main__":
    main()


