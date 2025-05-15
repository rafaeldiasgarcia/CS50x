#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    long cardNumber;
    do
    {
        cardNumber = get_long("Number: ");
    }
    while (cardNumber < 0);

    long tempCardNumber = cardNumber;
    int sum_of_doubled_digits = 0;
    int sum_of_other_digits = 0;
    int count = 0;
    bool is_second_digit = false;

    while (tempCardNumber > 0)
    {
        int digit = tempCardNumber % 10;

        if (is_second_digit)
        {
            int product = digit * 2;
            sum_of_doubled_digits += (product / 10) + (product % 10);
        }
        else
        {
            sum_of_other_digits += digit;
        }

        tempCardNumber /= 10;
        is_second_digit = !is_second_digit;
        count++;
    }

    int total_sum = sum_of_doubled_digits + sum_of_other_digits;
    bool luhn_valid = (total_sum % 10 == 0);

    if (luhn_valid)
    {
        long first_two_digits_calc = cardNumber;
        while (first_two_digits_calc >= 100)
        {
            first_two_digits_calc /= 10;
        }

        long first_digit_calc = cardNumber;
        while (first_digit_calc >= 10)
        {
            first_digit_calc /= 10;
        }

        if ((first_two_digits_calc == 34 || first_two_digits_calc == 37) && count == 15)
        {
            printf("AMEX\n");
        }
        else if ((first_two_digits_calc >= 51 && first_two_digits_calc <= 55) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (first_digit_calc == 4 && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
