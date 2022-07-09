/*
 * Filename: runoff.c
 *
 * Description: Implement a runoff (ranked-choice) election program.
 *
 *
 * Author: Steven Wong
 * Date: July 9, 2022
 */


#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate through the candidates array and check if the name is valid
    for (int i = 0; i < candidate_count; i++) { 
        // If the name is valid, record the vote in the preferences array and return true
        if (strcmp(name, candidates[i].name) == 0) { 
            preferences[voter][rank] = i; 
            return true;
        }
    }

    // If the name is invalid, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate through the preferences array and add the votes to the candidate's vote count
    for (int voter = 0; voter < voter_count; voter++) { 
        for (int choices = 0; choices < 3; choices++) {
            // Get the index of the candidate in the candidates array
            int currentCandidate = preferences[voter][choices];

            // If the current candidate isn't eliminated, update their vote count and go to next voter
            if (!candidates[currentCandidate].eliminated) {
                candidates[currentCandidate].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //Calculate the number of votes required to win the election
    int majorityCount = voter_count/2;
    // Iterate through the candidates array and check if a candidate has more than the majority count of votes
    for (int i = 0; i < voter_count; i++) { 
        if (candidates[i].votes > majorityCount) { 
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // If no candidate has more than the majority count of votes, return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize the minimum vote count to the number of voters
    int min = voter_count;

    // Iterate through the candidates array and check if the candidate has fewer votes than the minimum
    for (int i = 0; i < candidate_count; i++) {
        // If the candidate is eliminated, go to next candidate
        if (candidates[i].eliminated) { 
            continue;
        }

        // If the candidate has fewer votes than the minimum, update the minimum vote count
        if (candidates[i].votes < min) { 
            min = candidates[i].votes;
        }
    }
    // Return the minimum vote count
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate through the candidates array 
    for (int i = 0; i < candidate_count; i++) { 

        // If the candidate is eliminated, go to next candidate
        if (candidates[i].eliminated == true) { 
            continue;
        }

        // If there is a candidate with a different number of votes than the minimum, return false
        if (candidates[i].votes != min) { 
            return false;
        }
    }
    // If there is no candidate with a different number of votes than the minimum, return true
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through the candidates array
    for (int i = 0; i < candidate_count; i++) { 
        // If the candidate has the same number of votes as the minimum, eliminate them
        if (candidates[i].votes == min) { 
            candidates[i].eliminated = true;
        }
    }
    return;
}