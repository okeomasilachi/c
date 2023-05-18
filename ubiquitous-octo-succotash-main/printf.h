#ifndef MAIN_H
#define MAIN_H


#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void print_character(char ch);
void print_float(double d);
void print_integer(int i);
void print_string(char *s);
void print_unsigned_integer(unsigned int u);
void _printf(const char *format, ...);
int _putchar(char c);


#endif /* MAIN_H */
