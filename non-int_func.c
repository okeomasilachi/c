#include "main.h"

/**
 * _getline_2 - reads a line from a buffer
 *
 * @buffer: Pointer to the buffer
 * @buffer_pos: Pointer to the buffer position
 * @buffer_size: Pointer to the buffer size
 *
 * Return: Pointer to the read line
 */
char *_getline_2(char *buffer, int *buffer_pos, int *buffer_size)
{
	char *line = NULL;
	int line_size = 0;

	while (1)
	{
		if (*buffer_pos >= *buffer_size)
			read_input(buffer, buffer_pos, buffer_size);
		if (buffer[*buffer_pos] == '\n')
		{
			if (*buffer_pos + 1 < *buffer_size && buffer[*buffer_pos + 1] != '\n')
			{
				(*buffer_pos)++;
				continue;  /*Continue reading*/
			}
			else if (*buffer_pos + 1 < *buffer_size && buffer[*buffer_pos + 2] != '\n')
			{
				(*buffer_pos)++;
				continue;  /*Continue reading*/
			}
			(*buffer_pos)++;
			line = _realloc(line, line_size + *buffer_pos);
			_memcpy(line + line_size, buffer, *buffer_pos);
			line_size += *buffer_pos;
			line[line_size - 1] = '\0';
			return (line);
		}
		(*buffer_pos)++;
	}
	if (line != NULL)
	{
		line = _realloc(line, line_size + *buffer_pos);
		_memcpy(line + line_size, buffer, *buffer_pos);
		line_size += *buffer_pos;
		line[line_size - 1] = '\0';
	}
	return (line);
}

/**
 * p_Input_2 - getline process
 *
 * Return: pointer to the read characters
*/
char *p_Input_2()
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos, buffer_size;
	char *line;

	line = _getline_2(buffer, &buffer_pos, &buffer_size);

	return (line);
}

/**
 * p_Input - call all functions for reading from stdin
 *
 * Return: pointer to the read characters
*/
char *p_Input()
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos, buffer_size;
	char *line;

	read_input(buffer, &buffer_pos, &buffer_size);
	line = _getline(buffer, &buffer_pos, &buffer_size);

	return (line);
}
