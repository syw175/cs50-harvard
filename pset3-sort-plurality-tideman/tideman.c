/*
 * Filename: tideman.c
 *
 * Description: Implement a tideman (ranked-pairs) election program.
 *
 *
 * Author: Steven Wong
 * Date: June 30, 2022
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


// TEST FUNCTIONS --> Prototypes
void printPairs(void);
void printMatrix(void);

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
    // TEST FUNCTION --> Print out adjacency matrix 
    printf("Printing out the preferences or adjacency matrix\n"); 
    printMatrix();


    add_pairs();

    // TEST FUNCTION --> Print out pairs before the sort 
    printf("Pairs before the sort:\n");
    printPairs();


    sort_pairs();

    // TEST FUNCTION --> Print out pairs after the sort
    printf("Pairs after the sort:\n");
    printPairs();



    lock_pairs();
    print_winner();
    return 0;
}


// TEST FUNCTION --> Printing out adjacency Matrix 
void printMatrix(void) { 
    for (int i = 0; i < candidate_count; i++) { 
        for (int j = 0; j < candidate_count; j++) { 
            printf("%d ", preferences[i][j]); 
        }
        printf("\n");
    }
}


// TEST FUNCTION --> Printing out all pairs 
void printPairs(void) { 
    for (int i = 0; i < pair_count; i++) { 
        printf("Pair %d: Candidate %d won, Candidate %d lost\n", i+1, pairs[i].winner, pairs[i].loser);
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
    // TODO
    for (int y = 0; y < candidate_count; y++) { 
        for (int x = 0; x < candidate_count; x++) { 
            
            if (preferences[y][x] != preferences[x][y] && y > x) { 
                if (preferences[y][x] > preferences[x][y]) { 
                    pair currPair; 
                    currPair.winner = y;
                    currPair.loser = x;
                    pairs[pair_count] = currPair;
                    pair_count++;
                } else { 
                    pair currPair; 
                    currPair.winner = x;
                    currPair.loser = y;
                    pairs[pair_count] = currPair;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++) {
        int maxVictoryMarginIndex = i; 
        int pairWinner = pairs[i].winner;
        int pairLoser = pairs[i].loser;
        int maxStrength = preferences[pairWinner][pairLoser] - preferences[pairLoser][pairWinner];

        for (int j = i + 1; j < pair_count; j++) {

            int toCompareWinner = pairs[j].winner;
            int toCompareLoser = pairs[j].loser;
            int currentStrength = preferences[toCompareWinner][toCompareLoser] - preferences[toCompareLoser][toCompareWinner];
            
            if (currentStrength > maxStrength) {
                maxStrength = currentStrength; 
                maxVictoryMarginIndex = j;
            }

            pair temp = pairs[i];
            pairs[i] = pairs[maxVictoryMarginIndex];
            pairs[maxVictoryMarginIndex]= temp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}