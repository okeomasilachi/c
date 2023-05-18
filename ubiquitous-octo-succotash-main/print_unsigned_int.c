#include "printf.h"

/**
 * print_unsigned_integer - print unsigned int.
 * @u: unsigned int to print
 *
 * Description: This function prints unsigned int
 * Return: void
 */
void print_unsigned_integer(unsigned int u)
{
	int num_digits, i, j;
	unsigned int temp;
	char str[1024];

	if (u == 0)
	{
		_putchar('0');
	}
	else
	{
		num_digits = 0;
		temp = u;
		while (temp > 0)
		{
			num_digits++;
			temp /= 10;
		}

		for (i = num_digits - 1; i >= 0; i--)
		{
			str[i] = '0' + (u % 10);
			u /= 10;
		}
		for (j = 0; j < num_digits; j++)
		{
			_putchar(str[j]);
		}
	}
}
