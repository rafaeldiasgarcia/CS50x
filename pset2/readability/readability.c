#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;
    int length = strlen(text);

    if (length > 0)
    {
        words = 1; // Assume at least one word if the text is not empty
    }

    for (int i = 0; i < length; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            letters++;
        }
        else if (c == ' ')
        {
            words++;
        }
        else if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }

    float L = 0;
    float S = 0;

    if (words > 0)
    {
        L = (float) letters / words * 100.0;
        S = (float) sentences / words * 100.0;
    }

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
