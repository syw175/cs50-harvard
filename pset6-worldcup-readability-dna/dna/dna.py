import csv
import sys
from unicodedata import name

from numpy import true_divide


def main():

    # Check for correct command-line usage, if not, exit
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()


    # Read database file into a variable
    # {'Alice': {'AGATC': '2', 'AATG': '8', 'TATC': '3'}, 'Bob': {'AGATC': '4', 'AATG': '1', 'TATC': '5'}... }
    dnaDatabase = {}
    with open(sys.argv[1], 'r') as csvfile:
        reader = csv.DictReader(csvfile)
        # For each row in the database file, add the name and DNA sequence to the dictionary
        for row in reader:
            dnaDatabase[row['name']] = row
            # Remove the name key:pair from the dictionary values
            dnaDatabase[row['name']].pop('name')


    # Get list of all sequences in the database
    # ['AGATC', 'AATG', 'TATC', 'AGATC', 'AATG', 'TATC', 'AGATC', 'AATG', 'TATC']
    dnaSequences = []
    for name in dnaDatabase:
        # For each name, add the DNA sequence to the list
        for sequence in dnaDatabase[name]:
            dnaSequences.append(sequence)


    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file: 
        dnaSequence = file.read()


    # Find longest match of each STR in DNA sequence
    # {'AGATC': '4', 'AATG': '1', 'TATC': '5'}
    dnaSequenceMatches = {}
    for STR in dnaSequences:
        dnaSequenceMatches[STR] = str(longest_match(dnaSequence, STR))
    

    # Check database for matching profiles
    for person in dnaDatabase: 
        # If the DNA sequence matches the database, print the name and exit
        if dnaDatabase[person] == dnaSequenceMatches:
            print(person)
            sys.exit()


    # At this point, no match has been found in the database
    print("No match.")
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
