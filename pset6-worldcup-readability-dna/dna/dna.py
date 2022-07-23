import csv
import sys
from unicodedata import name


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()

    # Read database file into a variable
    # {'Alice': {'AGATC': '2', 'AATG': '8', 'TATC': '3'}, 'Bob': {'AGATC': '4', 'AATG': '1', 'TATC': '5'}, 'Charlie': {'AGATC': '3', 'AATG': '2', 'TATC': '5'}}
    dict = {}
    with open(sys.argv[1], "r") as file:
        fileReader = csv.DictReader(file)
        for row in fileReader: 
            name = row["name"]
            row.pop("name")
            dict[name] = row
    
    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file: 
        text = file.read()

    # TODO: Find longest match of each STR in DNA sequence

    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
