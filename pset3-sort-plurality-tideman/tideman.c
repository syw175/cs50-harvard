/*
 * Filename: tideman.c
 *
 * Description: Implement a tideman (ranked-pairs) election program.
 *
 *
 * Author: Steven Wong
 * Date: July 1, 2022
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
bool create_cycle(bool lockedArray[MAX][MAX], pair originPair, pair toAddPair);
int getMarginOfVictory(int pairIndex);




// TO REMOVE.....................................
// TEST FUNCTIONS --> Prototypes
void printPairs(void);
void printMatrix(void);
void printLocked(void);


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

    // TO REMOVE.....................................
    // TEST FUNCTION --> Print out adjacency matrix
    printf("Printing out the preferences or adjacency matrix\n");
    printMatrix();


    add_pairs();


    // TO REMOVE.....................................
    // TEST FUNCTION --> Print out pairs before the sort
    printf("\nPairs before the sort:\n");
    printPairs();


    sort_pairs();


    // TO REMOVE.....................................
    // TEST FUNCTION --> Print out pairs after the sort
    printf("\nPairs after the sort:\n");
    printPairs();


    // TO REMOVE.....................................
    // TEST FUNCTION --> Print out locked before locking in
    printf("\nLocked table before locking in\n");
    printLocked();


    lock_pairs();


    // TO REMOVE.....................................
    // TEST FUNCTION --> Print out locked after locking in
    printf("\nLocked table after locking in\n");
    printLocked();


    print_winner();
    return 0;
}


// TO REMOVE.....................................
// TEST FUNCTION --> Printing out adjacency Matrix
void printMatrix(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            printf("%d\t", preferences[i][j]);
        }
        printf("\n");
    }
}


// TO REMOVE................................
// TEST FUNCTION --> Printing out all pairs
void printPairs(void) {
    for (int i = 0; i < pair_count; i++) {
        printf("Pair %d: Candidate %d won, Candidate %d lost\n", i+1, pairs[i].winner, pairs[i].loser);
    }
    return;
}


// TO REMOVE................................
// TEST FUNCTION --> Printing out locked pairs
void printLocked(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int y = 0; y < candidate_count; y++) {
            printf(locked[i][y] ? "true\t" : "false\t");
        }
        printf("\n");
    }
    return;
}


// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int rows = 0; rows < candidate_count; rows++) {
        for (int cols = 0; cols < candidate_count; cols++) {
            if (preferences[rows][cols] > preferences[cols][rows]) {
                pair newPair = {rows, cols};
                pairs[pair_count] = newPair;
                pair_count++;
            }
        }
    }
    return;
}


// Sort pairs in decreasing order by strength of victory (Selection sort)
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        int maxVictoryMarginIndex = i;
        int maxStrength = getMarginOfVictory(i);

        for (int j = i + 1; j < pair_count; j++) {
            int currentStrength = getMarginOfVictory(j);

            if (getMarginOfVictory(j) > maxStrength) {
                maxStrength = currentStrength;
                maxVictoryMarginIndex = j;
            }
        }

        // Swap the next max margin of victory pair to the ith index position
        pair temp = pairs[i];
        pairs[i] = pairs[maxVictoryMarginIndex];
        pairs[maxVictoryMarginIndex]= temp;
    }
}


// Get the the margin of victory for the ith index pair of candidates from the array pairs
int getMarginOfVictory(int pairIndex)
{
    int winner = pairs[pairIndex].winner;
    int loser = pairs[pairIndex].loser;
    int marginOfVictory = preferences[winner][loser] - preferences[loser][winner];

    return marginOfVictory;
}



// TODO..........................................
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int y = 0; y < pair_count; y++) {
        // if (!create_cycle(locked, pairs[0], pairs[y])) {
        //     locked[pairs[y].winner][pairs[y].loser] = true;
        // }
        locked[pairs[y].winner][pairs[y].loser] = true;

    }
    return;
}


// TODO.........................................
// Determine if there would be a cycle by adding a new node to a graph
bool create_cycle(bool lockedArray[MAX][MAX], pair originPair, pair toAddPair) {
    return originPair.winner == toAddPair.loser;
    // return locked[originPair.winner][originPair.loser] == locked[toAddPair.winner][toAddPair.loser];
}


// Print the winner of the election
void print_winner(void)
{
    for (int cols = 0; cols < candidate_count; cols++) {
        bool found = true;
        for (int rows = 0; rows < candidate_count; rows++) {
            if (locked[rows][cols]) {
                found = false;
            }
        }

        if (found) {
            printf("%s\n", candidates[cols]);
            break;
        }
    }
    return;
}