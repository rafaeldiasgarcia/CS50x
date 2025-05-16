#include <cs50.h>
#include <stdio.h>
#include <string.h> // Para strcmp

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
} pair; // ESTA É A ÚNICA E CORRETA DEFINIÇÃO DA STRUCT PAIR

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; // Maximo de pares possiveis

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool check_cycle_recursive(int cycle_start_node,
                           int current_node); // Função auxiliar para lock_pairs
void lock_pairs(void);
void print_winner(void);

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

    // Clear graph of locked in pairs and preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0; // Inicializar preferences
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; // Armazena o índice do candidato
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Para cada par de candidatos (i, j) na ordem de preferência do eleitor
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // ranks[i] é o índice do candidato preferido sobre ranks[j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0; // Reset pair_count
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Usando Selection Sort para simplicidade
    for (int i = 0; i < pair_count - 1; i++)
    {
        int max_idx = i;
        // A força é a diferença absoluta de votos, ou apenas o número de votos do vencedor sobre o
        // perdedor A especificação diz "number of voters who prefer the preferred candidate" mas
        // para ordenar pela "força da vitória", a diferença é mais comum. No entanto, vamos seguir
        // a especificação: "number of voters who prefer the preferred candidate"
        // (preferences[winner][loser]) Para uma ordenação correta pela FORÇA (margem), seria: int
        // strength_max = preferences[pairs[i].winner][pairs[i].loser] -
        // preferences[pairs[i].loser][pairs[i].winner]; Mas se a especificação é estritamente
        // "número de votos do vencedor", então é:
        int strength_max = preferences[pairs[i].winner][pairs[i].loser];

        for (int j = i + 1; j < pair_count; j++)
        {
            // int strength_current = preferences[pairs[j].winner][pairs[j].loser] -
            // preferences[pairs[j].loser][pairs[j].winner]; // Para margem
            int strength_current =
                preferences[pairs[j].winner][pairs[j].loser]; // Para votos do vencedor
            if (strength_current > strength_max)
            {
                strength_max = strength_current;
                max_idx = j;
            }
        }
        // Trocar pairs[i] com pairs[max_idx]
        if (max_idx != i)
        {
            pair temp = pairs[i];
            pairs[i] = pairs[max_idx];
            pairs[max_idx] = temp;
        }
    }
    return;
}

// Função auxiliar recursiva para verificar se adicionar uma aresta de winner_idx para loser_idx
// criaria um ciclo. Fazemos isso verificando se já existe um caminho de loser_idx para winner_idx.
bool check_cycle_recursive(int start_node_of_potential_path, int end_node_of_potential_path)
{
    // Caso base: Se o início do caminho que estamos testando é o mesmo que o final,
    // encontramos um caminho de volta, o que significa um ciclo se a nova aresta for adicionada.
    if (start_node_of_potential_path == end_node_of_potential_path)
    {
        return true; // Ciclo encontrado (caminho de loser para winner existe)
    }

    // Percorrer todos os candidatos para ver para onde o start_node_of_potential_path aponta
    for (int i = 0; i < candidate_count; i++)
    {
        // Se existe uma aresta de start_node_of_potential_path para i
        if (locked[start_node_of_potential_path][i])
        {
            // Continuar a busca a partir de 'i' para encontrar 'end_node_of_potential_path'
            if (check_cycle_recursive(i, end_node_of_potential_path))
            {
                return true; // Ciclo encontrado mais abaixo na recursão
            }
        }
    }
    // Nenhum caminho encontrado de start_node_of_potential_path para end_node_of_potential_path por
    // este ramo
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Tenta adicionar a aresta pairs[i].winner -> pairs[i].loser
        // Para verificar o ciclo, precisamos ver se já existe um caminho
        // de pairs[i].loser (o perdedor da nova aresta) para pairs[i].winner (o vencedor da nova
        // aresta) Se tal caminho existir, adicionar a nova aresta (winner -> loser) fecharia um
        // ciclo.
        if (!check_cycle_recursive(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) // Para cada candidato 'i'
    {
        bool is_source = true;
        for (int j = 0; j < candidate_count;
             j++) // Verificar se algum candidato 'j' aponta para 'i'
        {
            if (locked[j][i]) // Se j está trancado sobre i (j -> i)
            {
                is_source = false; // Então 'i' não é uma fonte
                break;             // Não precisa verificar mais para este 'i'
            }
        }
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return; // Encontrou o vencedor, pode sair
        }
    }
    return;
}
