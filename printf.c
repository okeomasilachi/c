#include "main.h"

void pf(int stream, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;

            switch (*format) {
                case 'd': {
                    int num = va_arg(args, int);
		            print_integer(num, stream);
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
		            print_string(str, stream);
                    break;
                }
                case 'u': {
                    unsigned int num = va_arg(args, unsigned int);
		            print_unsigned_integer(num, stream);
                    break;
                }
                case 'c': {
                    int ch = va_arg(args, int);
		            print_character(ch, stream);
                    break;
                }
                default:
                    write(stream, format, 1);
                    break;
            }
        } else {
            write(stream, format, 1);
        }

        format++;
    }

    va_end(args);
}
