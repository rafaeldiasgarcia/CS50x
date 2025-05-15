#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_valid_key(string key);
char substitute_char(char p_char, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (!is_valid_key(key))
    {
        // A especificação permite uma "mensagem de erro de sua escolha".
        // Uma mensagem que cobre todas as condições de invalidade da chave.
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");

    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", substitute_char(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

bool is_valid_key(string key)
{
    int n = strlen(key);
    if (n != 26)
    {
        return false;
    }

    int seen[26] = {0}; // Array para rastrear letras (A-Z), inicializado com zeros

    for (int i = 0; i < n; i++)
    {
        char current_char_key = key[i];

        if (!isalpha(current_char_key))
        {
            return false; // Caractere não alfabético na chave
        }

        // Normaliza para maiúsculo para rastreamento
        char upper_char_key = toupper(current_char_key);
        int index = upper_char_key - 'A';

        if (seen[index] == 1)
        {
            return false; // Caractere duplicado na chave
        }
        seen[index] = 1; // Marca a letra como vista
    }
    // Se passou por todas as verificações, a chave é válida
    return true;
}

char substitute_char(char p_char, string key)
{
    if (isupper(p_char))
    {
        int index = p_char - 'A';
        return toupper(key[index]); // Preserva o case maiúsculo
    }
    else if (islower(p_char))
    {
        int index = p_char - 'a';
        return tolower(key[index]); // Preserva o case minúsculo
    }
    else
    {
        return p_char; // Retorna o caractere inalterado se não for uma letra
    }
}
