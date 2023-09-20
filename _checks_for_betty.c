/*
 * Description: A program that calculates the factorial of a given number.
 */

#include <stdio.h>

/*
 * Function: factorial
 * Description: Calculate the factorial of a given number.
 * Parameters:
 *   n: The input number for which to calculate the factorial.
 * Return: The factorial of n.
 */
unsigned long long factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;

    unsigned long long result = 1;

    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

int main(void)
{
    int num;

    printf("Enter a non-negative integer: ");
    scanf("%d", &num);

    if (num < 0)
    {
        printf("Factorial is not defined for negative numbers.\n");
    }
    else
    {
        unsigned long long fact = factorial(num);
        printf("Factorial of %d is %llu\n", num, fact);
    }

    return 0;
}

