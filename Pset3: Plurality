// a program to calculate the tally and declare the winner for an election, as defined by having a simple plurality of votes (aka the most of any of the candidates).

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            printf("Votes for %s: %i\n", candidates[i].name, candidates[i].votes);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // conditions tested
    bool breakk = true;
    bool tied = false;

    // declare to compare
    candidate winner = candidates[0];
    int m = candidates[0].votes;
    int startpoint = 0;

    for (int i = startpoint; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // if candidate in question has fewer votes
            if (m < candidates[j].votes)
            {
                breakk = false;
                tied = false;
                // declare a new winner
                winner = candidates[j];
                m = candidates[j].votes;
                startpoint = j;
            }

            else if (m == candidates[j].votes)
            {
                tied = true;
                breakk = false;
            }
        }

        if (breakk)
        {
            printf("%s\n", winner.name);
            return;
        }
    }

    // if there's a tie
    if (tied)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == m)
            {
                printf("%s\n", candidates[i].name);
            }
        }
        return;
    }

    printf("%s\n", winner.name);
    return;
}
