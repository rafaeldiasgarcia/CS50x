#include <cs50.h>  // Para get_string()
#include <stdio.h> // Para printf()

int main(void)
{
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
