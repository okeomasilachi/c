#include "main.h"

/**
 * 
*/
void print_integer(int num, int n)
{
	char buffer[32];
	int i = 0, j;
	
	if (num == 0)
	{
		write(n, "0", 1);
		return;
	}
	
	if (num < 0)
	{
		write(n, "-", 1);
		num = -num;
	}
	
	while (num != 0)
	{
		buffer[i++] = '0' + (num % 10);
		num /= 10;
	}
	
	for (j = i - 1; j >= 0; j--)
		write(n, &buffer[j], 1);
}

/**
 * 
*/
void write_string(int n, const char *s)
{
	write(n, s, strlen(s));
}

/**
 * print_string - print string lateral
 * @s:string to print
 * @n: stream
 *
 * Description: This function prints a string lateral
 * Return: void
 */
void print_string(char *s, int n)
{
	write_string(n, s);
}
