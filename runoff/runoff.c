#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i (predpichtenie po schetu g itogo cheloveka)
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status (struktura kandidatov s ih infoy)
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates (massiv kandidatov)
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

// Record preference if vote is valid   //Voter1 , rank - 1 ??????????, name - ???? ??????????
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][i] = rank;
            return true;
            printf("rank = %i", rank);
        }
    }
return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)           //for each voter
    {
        for (int p = 0; p < candidate_count; p++)   //for each candidate in his bulletine
        {
            if (!candidates[p].eliminated)          //if candidate is not eliminated add him 1 more vote
            {
                if (preferences[i][p] == 0)
                {
                    (candidates[p].votes += 1);
                    break;
                }
            }
            else if (candidates[p].eliminated)
            break;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int p = 0; p < candidate_count; p++)
    {
        if (candidates[p].votes > (voter_count * 1/2))
        {
        printf("%s wins!\n", candidates[p].name);
        return true;
        break;
        }
    }
return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimum = 0;
    for (int c = 0; c < candidate_count; c++)
    {
    if (candidates[c].votes < candidates[minimum].votes && !candidates[c].eliminated)
    minimum = c;
    }
    return candidates[minimum].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int out = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == min)
            out += 1;
        }
    if (out == candidate_count)
    {return true;}
    else
    {return false;}
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
     for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == min)
            candidates[i].eliminated = true;
        }
    return;
}