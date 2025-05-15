#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Variável para armazenar o troco em centavos
    int cents;

    // Loop para obter um valor de troco válido (maior ou igual a 0)
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0); // Condição para continuar pedindo: troco negativo

    // Variável para contar o número de moedas
    int coins = 0;

    // Calcular moedas de 25 centavos (Quarters)
    while (cents >= 25)
    {
        cents = cents - 25; // Ou cents -= 25;
        coins++;
    }

    // Calcular moedas de 10 centavos (Dimes)
    while (cents >= 10)
    {
        cents = cents - 10; // Ou cents -= 10;
        coins++;
    }

    // Calcular moedas de 5 centavos (Nickels)
    while (cents >= 5)
    {
        cents = cents - 5; // Ou cents -= 5;
        coins++;
    }

    // Calcular moedas de 1 centavo (Pennies)
    // O que sobrar aqui serão as moedas de 1 centavo
    // cada centavo restante é uma moeda de 1 centavo.
    coins = coins + cents; // Ou coins += cents;

    // Imprimir o número total de moedas
    printf("%i\n", coins);
}
