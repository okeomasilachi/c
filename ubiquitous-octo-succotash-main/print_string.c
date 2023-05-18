#include "printf.h"


/**
 * print_string - print string lateral
 * @s:string to print
 *
 * Description: This function prints a string lateral
 * Return: void
 */
void print_string(char *s)
{
	while (*s)
	{
		_putchar(*s);
		s++;
	}
}

