#include "main.h"
#include <stdio.h>

/**
 * binary_to_uint - Converts a binary number to an unsigned int
 * @b: Pointer to a string of 0 and 1 characters representing a binary number
 *
 * Return: The converted decimal number, or 0 if the input string is invalid
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int total = 0, power = 1;
	int len;

	/* Check for invalid input */
	if (b == NULL)
		return (0);

	/* Iterate through the string and check for invalid characters */
	for (len = 0; b[len]; len++)
	{
		if (b[len] != '0' && b[len] != '1')
			return (0);
	}

	/* Convert the binary number to decimal */
	for (len--; len >= 0; len--, power *= 2)
	{
		if (b[len] == '1')
			total += power;
	}

	return (total);
}
