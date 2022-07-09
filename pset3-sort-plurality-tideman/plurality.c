#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterate through candidates and check if name is a match
    for (int i = 0; i < candidate_count; i++) {
        // If the candidate is found, update their vote count and return true
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes++;
            return true;
        }
    }
    // If the candidate is not found, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Initialize max vote count to 0
    int maxVotes = 0;

    // Iterate over list a cnadidates to get the max value of votes
    for (int i = 0; i < candidate_count; i++) {
        // If the current candidate has more votes than the max, update max
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
        }
    }

    // Print candidates who have votes equal to the max votes
    for (int i = 0; i < candidate_count; i++) {
        // If the current candidate has the same votes as the max, print their name
        if (candidates[i].votes == maxVotes) {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}