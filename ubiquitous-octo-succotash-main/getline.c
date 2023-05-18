#include "main.h"

/* Define a global buffer to hold input read from standard input*/

static char buffer[BUFSIZE];
static int buffer_pos;
static int buffer_size;

/**
 * read_input - reads input from a buffer
 *
 * Return: read inputs
 */

void read_input(void)
{
	fflush(stdout);

	if (buffer_pos >= buffer_size)
	{
		buffer_size = read(STDIN_FILENO, buffer, BUFSIZE);
		if (buffer_size == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		if (buffer_size == 0)
		{
			_putchar('\n');
			exit(EXIT_SUCCESS);
		}
		buffer_pos = 0;
	}
}


/**
 * _getline - function reads from a buffer
 *
 *Return: the charactersread from the buffer
 */

char *_getline(void)
{
	char *line = NULL;
	int line_size = 0;

	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			read_input();
		}

		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			line = realloc(line, line_size + buffer_pos);
			_memcpy(line + line_size, buffer, buffer_pos);
			line_size += buffer_pos;
			line[line_size - 1] = '\0';

			return (line);
		}
		buffer_pos++;
	}

	if (line != NULL)
	{
		line = realloc(line, line_size + buffer_pos);
		_memcpy(line + line_size, buffer, buffer_pos);
		line_size += buffer_pos;
		line[line_size - 1] = '\0';
	}

	return (line);
}


