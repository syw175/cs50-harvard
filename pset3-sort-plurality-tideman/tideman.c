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

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool create_cycle(pair toAddPair);
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
bool vote(int rank, string name, int ranks[]) {
    
    // Iterate through the new vote and update the ranks array
    for (int i = 0; i < candidate_count; i++) {

        // Check if a candidate is valid and if it is, update the ranks array and return true
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    // If the candidate is not valid, return false
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {

    // Iterate through the ranks array and update the preferences matrix
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {

    // Iterate through the rows of the preferences matrix
    for (int rows = 0; rows < candidate_count; rows++) {
        // Iterate through the columns of the preferences matrix
        for (int cols = 0; cols < candidate_count; cols++) {

            // If there is a preference for candidate i over candidate j...
            if (preferences[rows][cols] > preferences[cols][rows]) {
                // Create a new pair and add it to the array of pairs
                pair newPair = {rows, cols};
                pairs[pair_count] = newPair;
                pair_count++;
            }
        }
    }
    return;
}


// Sort pairs in decreasing order by strength of victory (Selection sort)
void sort_pairs(void) {

    // Iterate through the pairs array
    for (int i = 0; i < pair_count; i++) {
        int maxVictoryMarginIndex = i;
        int maxStrength = getMarginOfVictory(i);

        // Iterate through the pairs array from the current index to the end
        for (int j = i + 1; j < pair_count; j++) {
            int currentStrength = getMarginOfVictory(j);

            // If the current pair has a stronger victory margin than the max pair, update the max pair
            if (getMarginOfVictory(j) > maxStrength) {
                maxStrength = currentStrength;
                // Update the max victory margin index
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
    for (int y = 0; y < pair_count; y++) 
    {
        // If adding the pair does not create a cycle...
        if (!create_cycle(pairs[y]))
        {
            // Lock the pair by setting the locked matrix to true
            locked[pairs[y].winner][pairs[y].loser] = true;
        }
    }
    return;
}


// TODO.........................................
// Determine if there would be a cycle by adding a new node to a graph
bool create_cycle(pair toAddPair) 
{

    // if next points to origin then we're adding a cycle
    // loop through lockedArray and check if we can get back to origin


    return false;

    // origin = toAddPair
    // loop
    // for nodes in lockedArray[origin].items is there a next
    //   if entire row is 0 then no next then just exit loop and we can add pair
    //   else check if one of the 1s gets us back to originPair then return false
    //             for each 1 in row create_cycle(origin, that one)
    // next


    // return locked[originPair.winner][originPair.loser] == locked[toAddPair.winner][toAddPair.loser];
}


// Print the winner of the election
void print_winner(void) {

    // Iterate through the locked array
    for (int cols = 0; cols < candidate_count; cols++) {
        bool found = true;

        // If the column is all true, then the candidate is the winner
        for (int rows = 0; rows < candidate_count; rows++) {
            if (locked[rows][cols]) {
                found = false;
            }
        }

        // If found is true, then the candidate is the winner
        if (found) {
            printf("%s\n", candidates[cols]);
            break;
        }
    }
    return;
}