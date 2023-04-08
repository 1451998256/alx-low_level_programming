#include "main.h"
#include <stdio.h>

/**
 * print_binary - Prints the binary representation of a number
 * @n: Decimal number to print as binary
 */
void print_binary(unsigned long int n)
{
	unsigned long int temp = n;
	int shifts = 0;

	/* If the number is zero, print 0 and return */
	if (n == 0)
	{
		printf("0");
		return;
	}

	/* Determine the number of binary digits required to represent the number */
	while (temp != 0)
	{
		temp >>= 1;
		shifts++;
	}

	/* Print the binary digits in reverse order */
	for (; shifts > 0; shifts--)
	{
		if ((n >> (shifts - 1)) & 1)
			printf("1");
		else
			printf("0");
	}
}
