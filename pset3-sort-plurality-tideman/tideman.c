/*
 * Filename: tideman.c
 *
 * Description: Implement a tideman (ranked-pairs) election program.
 *
 *
 * Author: Steven Wong
 * Date: July 24, 2022
 */


#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

// Initialize pair and candidate counts
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool create_cycle(int winner, int loser);
int getMarginOfVictory(int pairIndex);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();

    print_winner();
    return 0;
}


// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) 
{    
    // Iterate through the new vote and update the ranks array
    for (int i = 0; i < candidate_count; i++) 
    {
        // Check if a candidate is valid and if it is, update the ranks array and return true
        if (strcmp(name, candidates[i]) == 0) 
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If the candidate is not valid, return false
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[]) 
{
    // Iterate through the ranks array and update the preferences matrix
    for (int i = 0; i < candidate_count; i++) 
    {
        for (int j = i + 1; j < candidate_count; j++) 
        {
            // Increment the preferences matrix for the pair of candidates
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void) 
{
    // Iterate through the rows of the preferences matrix
    for (int rows = 0; rows < candidate_count; rows++) 
    {
        // Iterate through the columns of the preferences matrix
        for (int cols = 0; cols < candidate_count; cols++) 
        {
            // If there is a preference for candidate i over candidate j...
            if (preferences[rows][cols] > preferences[cols][rows]) 
            {
                // Create a new pair and add it to the array of pairs
                pair newPair = {rows, cols};
                pairs[pair_count] = newPair;
                // Increment the pair count
                pair_count++;
            }
        }
    }
    return;
}


// Sort pairs in decreasing order by strength of victory (Selection sort)
void sort_pairs(void) 
{
    // Iterate through the pairs array
    for (int i = 0; i < pair_count; i++) 
    {
        // Set the max victory to the ith pair
        int maxVictoryMarginIndex = i;
        int maxStrength = getMarginOfVictory(i);

        // Iterate through the pairs array from the current index to the end
        for (int j = i + 1; j < pair_count; j++) 
        {
            // Get the strength of victory for the jth pair
            int currentStrength = getMarginOfVictory(j);

            // If the current pair has a stronger victory margin than the max pair, update the max pair
            if (getMarginOfVictory(j) > maxStrength) 
            {
                maxStrength = currentStrength;
                maxVictoryMarginIndex = j;
            }
        }

        // Swap the pair at index i with the pair at index maxVictoryMarginIndex
        pair temp = pairs[i];
        pairs[i] = pairs[maxVictoryMarginIndex];
        pairs[maxVictoryMarginIndex]= temp;
        return;
    }
}


// Returns the margin of victory for the ith index pair of candidates from the array pairs
int getMarginOfVictory(int pairIndex) {

    // Get the winner and loser of the pair
    int winner = pairs[pairIndex].winner;
    int loser = pairs[pairIndex].loser;

    // Get the margin of victory for the pair
    int marginOfVictory = preferences[winner][loser] - preferences[loser][winner];

    // Return the margin of victory
    return marginOfVictory;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate through the pairs array
    for (int i = 0; i < pair_count; i++) 
    {
        pair currentPair = pairs[i];
        // If adding the pair does not create a cycle...
        if (!create_cycle(currentPair.winner, currentPair.loser))
        {
            // Lock the pair by setting the locked matrix to true
            locked[currentPair.winner][currentPair.loser] = true;
        }
    }
    return;
}


// Determine if there would be a cycle by adding a new node to a graph
bool create_cycle(int winner, int loser) 
{
    // Base case: If the winner points to itself and creates a cycle, return true
    if (locked[loser][winner])
    {
        return true;
    }

    // Recursive Case: Iterate through the locked array 
    for (int i = 0; i < candidate_count; i++)
    {
        // If there is path between the loser and the ith candidate.. 
        if (locked[loser][i])
        {
            // If the ith candidate points to the winner and creates a cycle, return true
            if (create_cycle(winner, i))
            {
                return true;
            }
        }
    }



    //     // If there is a path between the winner and i, and i is not the loser,return true
    //     if (locked[loser][i] && create_cycle(winner, i))
    //     {
    //         return true;
    //     }
    // }
    // At this point, there is no path between the winner and loser, so return false
    return false;
}


// Print the winner of the election
void print_winner(void) 
{
    // Iterate through the locked array
    for (int cols = 0; cols < candidate_count; cols++) 
    {
        // Set the found variable to an initial value of true
        bool found = true;

        // If the column is all true, then the candidate is the winner
        for (int rows = 0; rows < candidate_count; rows++) 
        {
            // If the locked array has a 0 at the ith row and the ith column...
            if (locked[rows][cols]) 
            {
                // Set the found variable to false
                found = false;
            }
        }

        // If found is true at this point, then the candidate is the winner
        if (found) 
        {
            // Print the winner and exit the loop
            printf("%s\n", candidates[cols]);
            break;
        }
    }
    return;
}