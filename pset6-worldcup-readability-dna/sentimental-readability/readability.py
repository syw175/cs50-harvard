


def main(): 

    letterCount = 0;
    wordCount = 0; 
    sentenceCount = 0;

    gradeIndex = getColemanIndex(letterCount, wordCount, sentenceCount)

    # Print the grade level
    if (gradeIndex >= 16):
        print("Grade 16+");

    elif (gradeIndex > 1):
        print(f"Grade {gradeIndex}")

    else:
        print("Before Grade 1")
    


def getColemanIndex(letterCount, wordCount, sentenceCount): 
    return




if __name__ == "__main__":
    main()


