#include "main.h"


void print_integer(int num, int n) {
    char buffer[32];
    int i = 0, j;

    if (num == 0) {
        write(n, "0", 1);
        return;
    }

    if (num < 0) {
        write(n, "-", 1);
        num = -num;
    }

    while (num != 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    for (j = i - 1; j >= 0; j--)
        write(n, &buffer[j], 1);
}

/**
 * print_character - print char
 * @ch: char to print
 *
 * Description: This function prints characters
 * Return: void
 */

void print_character(char ch, int n) {
    write(n, &ch, 1);
}


void write_string(int n, const char *s) {
    write(n, s, strlen(s));
}

/**
 * print_string - print string lateral
 * @s:string to print
 *
 * Description: This function prints a string lateral
 * Return: void
 */
void print_string(char *s, int n) {
    write_string(n, s);
}

/**
 * print_unsigned_integer - print unsigned int.
 * @u: unsigned int to print
 *
 * Description: This function prints unsigned int
 * Return: void
 */

void print_unsigned_integer(unsigned int u, int n) {
    char buffer[32];
    int i = 0, j;

    if (u == 0) {
        write(n, "0", 1);
        return;
    }

    while (u != 0) {
        buffer[i++] = '0' + (u % 10);
        u /= 10;
    }

    for (j = i - 1; j >= 0; j--)
        write(n, &buffer[j], 1);
}