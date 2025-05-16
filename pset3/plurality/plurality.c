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
} candidate;

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
    // Iterate over each candidate (from 0 up to candidate_count - 1)
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the current candidate's name (candidates[i].name)
        // matches the 'name' provided as an argument.
        // strcmp(s1, s2) returns 0 if s1 and s2 are identical.
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If the names match, this vote is for this candidate.
            // Increment this candidate's vote count.
            candidates[i].votes++;
            // The vote was valid and recorded, so return true.
            return true;
        }
    }

    // If the loop finishes and we haven't found a candidate with that name,
    // the vote is invalid. Return false.
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Find the maximum number of votes
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Print the candidate (or candidates) with maximum votes
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == max_votes)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    // No explicit return needed for a void function's end
}
