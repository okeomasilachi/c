#include "printf.h"
/**
 * print_float - print float
 * @d: float number to print
 *
 * Description: Prints floating point number.
 * Return: void
 */
void print_float(double d)
{
	int integer_part = (int) d;
	int num_digits, num_decimal_digits, temp, digit, i, j, k;
	double fraction_part = d - integer_part;
	char str[1024];

	if (integer_part < 0)
	{
		_putchar('-');
		integer_part = -integer_part;
	}
	if (integer_part == 0)
		_putchar('0');

	else
	{
		num_digits = 0;
		temp = integer_part;
		while (temp > 0)
		{
			num_digits++;
			temp /= 10;
		}

		for (i = num_digits - 1; i >= 0; i--)
		{
			str[i] = '0' + (integer_part % 10);
			integer_part /= 10;
		}
		for (j = 0; j < num_digits; j++)
			_putchar(str[j]);
	}
	_putchar('.');/*Print decimal point*/
	num_decimal_digits = 6; /* Number of decimal digits*/
	for (k = 0; k < num_decimal_digits; k++)
	{
		fraction_part *= 10;
		digit = (int) fraction_part;
		_putchar('0' + digit);
		fraction_part -= digit;
	}
}
