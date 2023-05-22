#include "main.h"

/**
 * 
*/
void pf(int stream, const char* format, ...)
{
	va_list args;

	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'd':
				{
					int num = va_arg(args, int);
					print_integer(num, stream);
					break;
				}
				case 's':
				{
					char* str = va_arg(args, char*);
					print_string(str, stream);
					break;
				}
				default:
					write(stream, format, 1);
					break;
			}
		}
		else
		{
			write(stream, format, 1);
		}
		format++;
	}
	va_end(args);
}

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
	write(n, s, _strlen(s));
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

/**
 * 
*/
int _isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}